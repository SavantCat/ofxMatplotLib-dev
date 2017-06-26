#pragma once

#include "ofMain.h"

#include "pybind11/pybind11.h"
#include "pybind11/eval.h"
#include "pybind11/stl.h"

namespace py = pybind11;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofImage plotImg;

		bool GetPlotImage(vector<float> &x, vector<float> &y, ofImage &dist) {

			ofImage tempImg;

			bool isGet = false;

			auto th = std::thread([&] {

				wchar_t* program = Py_DecodeLocale("", nullptr);
				if (program == nullptr) {
					fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
					exit();
				}
				Py_SetProgramName(program);
				Py_InitializeEx(0);

				try {
					auto global = py::dict(py::module::import("__main__").attr("__dict__"));
					auto local = py::dict();

					double x0 = -10.0;
					double xn = 20.0;
					char line[1024];

					string plot = "x = np.linspace(%f, %f, 1000)";

					sprintf(line, plot.c_str(), x0, xn);

					string import = {
						"import io\n"
						"import numpy as np\n"
						"import matplotlib.pyplot as plt\n"
						"from PIL import Image\n"
						"from numpy.random import *"
					};
					py::eval<py::eval_statements>(import.c_str(), global, local);

					local["x"] = x;
					local["y"] = y;

					string code = {
						"plt.clf()\n"
						"plt.plot(x, y)\n"
						"buf = io.BytesIO()\n"
						"plt.savefig(buf, format='png')\n"
						"buf.seek(0)\n"
						"img = Image.open(buf)\n"
						"pixels = img.load()\n"
						"dataList = []\n"
						"img_x = img.size[0]\n"
						"img_y = img.size[1]\n"
						"for y in range(img_y):\n"
						"    for x in range(img_x):\n"
						"        for c in range(3):\n"
						"            dataList.append(pixels[x, y][c])\n"
					};
					py::eval<py::eval_statements>(code.c_str(), global, local);

					int size_x = local["img_x"].cast<int>();
					int size_y = local["img_y"].cast<int>();

					unsigned char *pixelBuffer = new unsigned char[size_x*size_y * 3];

					int pos = 0;
					for (auto pix : local["dataList"]) {
						pixelBuffer[pos] = pix.cast<unsigned char>();
						pos++;
					}

					ofPixels pix;
					pix.setFromPixels(pixelBuffer, size_x, size_y, OF_IMAGE_COLOR);
					tempImg.setFromPixels(pix);
					tempImg.update();

					isGet = true;
				}
				catch (py::error_already_set& e) {
					std::cout << "Python error.\n" << e.what() << "\n";
				}

				PyMem_RawFree(program);

			});
			th.join();

			dist = tempImg;

			return isGet;
		}
};
