#include "data_Opti.h"

bool qrcode::isZeroAll(Eigen::VectorXi & block)
{
	for (int i = 0; i < block.size(); i++) {
		if (block[i] != 0) {
			return false;
			break;
		}
	}
	return true;
}

void qrcode::sortLabelArea(int & labelIndex, Eigen::MatrixXi & label, Eigen::MatrixXd & area, Eigen::MatrixXd & labelArea, Eigen::MatrixXd & sortLabelArea)
{	
	int n = 0;
	for (int i = 0; i < area.rows(); i++) {
		for (int j = 0; j < area.cols(); j++) {
			if (label(i, j) == labelIndex) {
				n++;
			}
		}
	}
	labelArea.resize(n, 3);
	//std::cout << "n:" << n << std::endl;
	std::vector<Eigen::Vector3d> temp;
	int k = 0;
	for (int i = 0; i < area.rows(); i++) {
		for (int j = 0; j < area.cols(); j++) {
			if (label(i, j) == labelIndex) {
				//std::cout << "k:" << k << std::endl;
				labelArea(k, 0) = i;
				labelArea(k, 1) = j;
				labelArea(k, 2) = area(i, j);
				//std::cout << labelArea.row(k) << std::endl;
				temp.emplace_back(i, j, area(i, j));
				k++;				
			}
		}
	}
	//std::cout <<"labelArea: "<< labelArea << std::endl;

	std::stable_sort(temp.begin(), temp.end(), [](Eigen::Vector3d v1, Eigen::Vector3d v2) {return v1(2) > v2(2); });
	Eigen::MatrixXd sortLabelArea1;
	sortLabelArea1.resize(n, 3);
	for (int i = 0; i < n; i++) sortLabelArea1.row(i) = temp[i].transpose();
	sortLabelArea.resize(n, 4);
	for (int i = 0; i < n; i++) {
		sortLabelArea.row(i) << i, sortLabelArea1(i, 0), sortLabelArea1(i, 1), sortLabelArea1(i, 2);
	}
	//std::cout << "sortLabelArea: " << sortLabelArea << std::endl;
}

void qrcode::sortLabelArea(int & labelIndex, Eigen::MatrixXi & label, Eigen::MatrixXd & area, Eigen::MatrixXd & sortLabelArea)
{
	int n = 0;
	for (int i = 0; i < area.rows(); i++) {
		for (int j = 0; j < area.cols(); j++) {
			if (label(i, j) == labelIndex) {
				n++;
			}
		}
	}

	Eigen::MatrixXd labelArea;
	labelArea.resize(n, 3);
	//std::cout << "n:" << n << std::endl;
	std::vector<Eigen::Vector3d> temp;
	int k = 0;
	for (int i = 0; i < area.rows(); i++) {
		for (int j = 0; j < area.cols(); j++) {
			if (label(i, j) == labelIndex) {
				//std::cout << "k:" << k << std::endl;
				labelArea(k, 0) = i;
				labelArea(k, 1) = j;
				labelArea(k, 2) = area(i, j);
				//std::cout << labelArea.row(k) << std::endl;
				temp.emplace_back(i, j, area(i, j));
				k++;
			}
		}
	}
	//std::cout <<"labelArea: "<< labelArea << std::endl;

	std::stable_sort(temp.begin(), temp.end(), [](Eigen::Vector3d v1, Eigen::Vector3d v2) {return v1(2) > v2(2); });
	Eigen::MatrixXd sortLabelArea1;
	sortLabelArea1.resize(n, 3);
	for (int i = 0; i < n; i++) sortLabelArea1.row(i) = temp[i].transpose();
	temp.clear();
	sortLabelArea.resize(n, 4);
	for (int i = 0; i < n; i++) {
		sortLabelArea.row(i) << i, sortLabelArea1(i, 0), sortLabelArea1(i, 1), sortLabelArea1(i, 2);
	}
	//std::cout << "sortLabelArea: " << sortLabelArea << std::endl;
}

void qrcode::data_Optimization(std::vector<std::vector<qrgen::Pixel>>& pixels, 
	Eigen::VectorXi & block,
	Eigen::VectorXi & codeword, 
	Eigen::MatrixXi & modules, 
	Engine * engine, 
	int scale)
{
	static int opt_module = 0;
	static int opt_area = 0;
	float min, max;
	int count = 0;
	while (!isZeroAll(block)) {
		
		//Calculate the visible area of each modules, fist bwlabel: label, then halfedge bounds, finally 2D visibility and area: pixel_propertys[i][j].area.
		Eigen::MatrixXi label;
		std::vector<int> num;
		qrcode::bwlabel(engine, modules, 4, label, num);

		Eigen::MatrixXd area;
		qrcode::visualarea(engine, modules, label, area);
		if (count == 0) {
			min = area.minCoeff();
			max = area.maxCoeff() * 0.9;
		}
	
		std::string out_area_png_file = "D:/git/QR_optimization/build/image/area" + std::to_string(opt_area) + ".png";
		opt_area++;
		//qrcode::write_area(out_area_png_file, pixels, area, min, max, scale);
		qrcode::write_area(out_area_png_file, area, min, max, scale);

		//Calculate the average area of connect component
		Eigen::MatrixXd avAreaSort;
		qrcode::averageArea(area, label, num, avAreaSort);

		bool inLabel = false;
		int labelIndex = 0;
		
		while (!inLabel) {

			int numLabel = avAreaSort(labelIndex, 1);
			Eigen::MatrixXd sortLabelArea;
			qrcode::sortLabelArea(numLabel, label, area, sortLabelArea);
			bool isThis = false;
			int moduleIndex = 0;
			
			while (!isThis) {

				int module_row = sortLabelArea(moduleIndex, 1);
				int module_col = sortLabelArea(moduleIndex, 2);
				//std::cout << "module_row" << module_row << std::endl;
				//std::cout << "module_col" << module_col << std::endl;
				qrgen::Pixel pixel = pixels[module_row - 4][module_col - 4];
				if (pixel.getPixelRole() == qrgen::Pixel::PixelRole::DATA ||
					pixel.getPixelRole() == qrgen::Pixel::PixelRole::CHECK ||
					pixel.getPixelRole() == qrgen::Pixel::PixelRole::EXTRA) {

					int codewordIndex = pixel.getCodeWordIndex();
					int blockIndex = pixel.getBlockIndex();

					if (codeword[codewordIndex] == 0) {						
						if (block[blockIndex] > 0) {
							codeword[codewordIndex] = 1;
							block[blockIndex] -= 1;
							modules(module_row, module_col) = 0;
							isThis = true;
							inLabel = true;
						}						
					}
					if (codeword[codewordIndex] == 1) {
						//codeword[codewordIndex] = 1;
						modules(module_row, module_col) = 0;
						isThis = true;
						inLabel = true;
					}

				}

				if (moduleIndex < sortLabelArea.rows() - 1) {
					moduleIndex++;
				}
				else {
					break;
				}
				
			}

			labelIndex++;
		}
		
		//update
		std::string out_qr_png_file = "D:/git/QR_optimization/build/image/opti" + std::to_string(++opt_module) + ".png";
		qrcode::write_png(out_qr_png_file, modules, scale);
		if (isZeroAll(block)) {
			//opt_area++;			
			qrcode::bwlabel(engine, modules, 4, label, num);		
			qrcode::visualarea(engine, modules, label, area);
			out_area_png_file = "D:/git/QR_optimization/build/image/area" + std::to_string(opt_area) + ".png";
			//qrcode::write_area(out_area_png_file, pixels, area, min, max, scale);
			qrcode::write_area(out_area_png_file, area, min, max, scale);
		}
		count++;
		std::cout << "iteration:" << count << std::endl;
	}
}