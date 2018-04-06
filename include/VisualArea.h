// This project is about 3d QR code generating,see more details at https://github.com/swannyPeng/3dqrcode_libigl
// 
// Copyright (C) 2017 Swanny Peng <ph1994wh@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VISUALAREA_H_
#define VISUALAREA_H_

#include <igl/matlab/matlabinterface.h>
#include <Eigen/core>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <igl/triangle/triangulate.h>
#include <igl/sort.h>
#include "PixelProperty.h"
#include "bwlabel.h"
#include "raw_to_visible_polygon.h"
namespace qrcode {
	//void visualarea(Engine* engine, Eigen::MatrixXi &modules, Eigen::MatrixXi &functions, std::vector<std::vector<qrgen::PixelProperty>>&pixel_propertys);
	void visualarea(Engine * engine, Eigen::MatrixXi & modules, Eigen::MatrixXi & label, std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys);
	void visualarea(Engine * engine, Eigen::MatrixXi & modules, Eigen::MatrixXi & label, Eigen::MatrixXd & area);
	void visualarea(Engine * engine, Eigen::MatrixXi & modules, Eigen::MatrixXi & label, std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys, Eigen::MatrixXd & area);
	double triArea(Eigen::MatrixXd & V, Eigen::MatrixXi & F);
	//void visualarea(Engine * engine, Eigen::MatrixXi & modules, Eigen::MatrixXi & label, int label_num, std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys);

	void averageArea(std::vector<std::vector<qrgen::PixelProperty>>&pixel_propertys, Eigen::MatrixXi & label, std::vector<int>& num, std::vector<double>& averageArea);
	void averageArea(std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys, Eigen::MatrixXi & label, std::vector<int>& num, Eigen::MatrixXd & averageArea, Eigen::MatrixXd & averageAreaSort, Eigen::MatrixXd & I);
	void averageArea(Eigen::MatrixXd & area, Eigen::MatrixXi & label, std::vector<int>& num, Eigen::MatrixXd & averageArea, Eigen::MatrixXd & averageAreaSort, Eigen::MatrixXd & I);
	void averageArea(Eigen::MatrixXd & area, Eigen::MatrixXi & label, std::vector<int>& num, Eigen::MatrixXd & averageArea, Eigen::MatrixXd & averageAreaSort);
	void averageArea(Eigen::MatrixXd & area, Eigen::MatrixXi & label, std::vector<int>& num, Eigen::MatrixXd & averageAreaSort);
}

#endif // !VISUALAREA_H_

