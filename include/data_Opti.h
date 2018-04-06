// This project is about QR Code Data optimization.
// 
// Copyright (C) 2017 Lorrain <lorrain0407@gmail.com>
#pragma once

#include<Eigen/core>
#include<vector> 
#include <algorithm>
#include <igl/matlab/matlabinterface.h>
#include <igl/sort.h>

#include "Qrcoder.h"
#include "PixelProperty.h"
#include "Pixel.h"
#include "bwlabel.h"
#include "VisualArea.h"
#include "writePNG.h"

namespace qrcode {
	bool isZeroAll(Eigen::VectorXi & block);
	void sortLabelArea(int & labelIndex, Eigen::MatrixXi & label, Eigen::MatrixXd & area, Eigen::MatrixXd & labelArea, Eigen::MatrixXd & sortLabelArea);
	void sortLabelArea(int & labelIndex, Eigen::MatrixXi & label, Eigen::MatrixXd & area, Eigen::MatrixXd & sortLabelArea);
	void data_Optimization(std::vector<std::vector<qrgen::Pixel>>& pixels,
		Eigen::VectorXi & block,
		Eigen::VectorXi & codeword,
		Eigen::MatrixXi & modules,
		Engine * engine,
		int scale);
}