// This project is about 3d QR code generating,see more details at https://github.com/swannyPeng/3dqrcode_libigl
// 
// Copyright (C) 2017 Swanny Peng <ph1994wh@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#ifndef WRITE_PNG_H_
#define WRITE_PNG_H_
#include <string>
#include <Eigen/dense>
#include <igl/png/writePNG.h>
#include<igl/jet.h>
#include "Qrcoder.h"
#include "Pixel.h"
#include "jet.h"

namespace qrcode {
	void write_png(std::string file, Eigen::MatrixXi &modules, int scale);
	//void write_png(std::string file, Eigen::MatrixXi & modules, Eigen::MatrixXi & modules_c, int scale);
	//void write_png1(std::string file,Eigen::MatrixXi & modules, Eigen::MatrixXi & modules_c, int scale);
	//void write_png(std::string file, Eigen::MatrixXi &modules);
	void write_png(std::string file, std::vector<std::vector<qrgen::Pixel>> pixels, Eigen::MatrixXi &modules, int scale);
	void write_area(std::string file, Eigen::MatrixXd & area);
	void write_area(std::string file, Eigen::MatrixXd & area, float  min, float  max, int scale);
	void write_area(std::string file, std::vector<std::vector<qrgen::Pixel>> pixels, Eigen::MatrixXd & area, float  min, float  max, int scale);
}
#endif // !WRITE_PNG_H_

