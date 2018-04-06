// This project is about QR Code Data optimization.
// 
// Copyright (C) 2017 Lorrain <lorrain0407@gmail.com>

#include <iostream>
using namespace std;
#include <igl/matlab/matlabinterface.h>
#include <igl/Timer.h>
#include <Eigen/core>
#include "Qrcoder.h"
#include "writePNG.h"
#include "VisualArea.h"
#include "data_Opti.h"

int main(int argc, char *argv[])
{
	/*Matlab instance*/
	Engine *engine;
	igl::matlab::mlinit(&engine);

	/*Timer*/
	igl::Timer timer;

	//Input a text, and generate relative information: pixels
	string text = "Welcome to join us!∑¢ÀÕºÚ¿˙÷¡3dincrement@gmail.com";
	qrgen::Bits bits;
	qrgen::LEVEL level = qrgen::LEVEL::H;
	qrgen::Mask * mask = new qrgen::Mask(3);
	qrgen::Version *version = qrgen::getMinVersion(text, level, bits);
	std::vector<std::vector<qrgen::Pixel>> pixels = qrgen::encode(bits, version, level, mask);
    std::cout << version->getVersion() << std::endl;
	//qrgen::toSvgString("D:/git/QR_optimization/build/image/Bumpy_H_3.svg", pixels, 4);

	//Output the QR png about the text, you can set the scale of a module
	Eigen::MatrixXi modules(pixels.size() + 8, pixels.size() + 8);
	modules.setConstant(modules.rows(), modules.cols(), 0);
	for (int i = 4; i < 4 + pixels.size(); i++) {
		for (int j = 4; j < 4 + pixels.size(); j++) {
			modules(i, j) = pixels[i - 4][j - 4].getPixel();
		}
	}
	int scale = 5;
	string out_qr_png_file = "D:/git/QR_optimization/build/image/" + text + "_H_M3_V" + std::to_string(version->getVersion()) + ".png";
	qrcode::write_png(out_qr_png_file, modules, scale);

	//get version and init its codewords and block
	qrgen::VerInfo verInfo = version->VERSION_INFOS[version->getVersion()];
	int num_codeword = verInfo.bytes;    //whole codewords
	int num_block = verInfo.lvlInfos[3].num_of_block;
	int num_codeword_block = (verInfo.lvlInfos[3].cbytes_pre_block *  verInfo.lvlInfos[3].num_of_block - verInfo.lvlInfos[0].cbytes_pre_block *  verInfo.lvlInfos[0].num_of_block) / 2 / verInfo.lvlInfos[3].num_of_block;
	//cout << "num_codeword:" << num_codeword << endl;
	//cout << "num_block:" << num_block << endl;
	//cout << "num_codeword_block:" << num_codeword_block << endl;

	Eigen::VectorXi block(num_block);
	block.setConstant(num_codeword_block);
	Eigen::VectorXi codeword;
	codeword.setZero(num_codeword);

	//Eigen::MatrixXd labelArea;
	//Eigen::MatrixXd sortLabelArea;
	//int labelIndex = 20;
	//qrcode::sortLabelArea(labelIndex, label, area, labelArea, sortLabelArea);
	//qrcode::sortLabelArea(labelIndex, label, area, sortLabelArea);

	//data optimization
	qrcode::data_Optimization(pixels, block, codeword, modules, engine, scale);
	
	system("pause");
}