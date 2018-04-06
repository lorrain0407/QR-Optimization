#include "writePNG.h"
void qrcode::write_png(std::string file, Eigen::MatrixXi & modules, int scale)
{
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
	R.resize((modules.rows())*scale, (modules.cols())*scale);
	G.resize((modules.rows())*scale, (modules.cols())*scale);
	B.resize((modules.rows())*scale, (modules.cols())*scale);
	A.resize((modules.rows())*scale, (modules.cols())*scale);
	for (int i = 0; i < modules.rows(); i++) {
		for (int j = 0; j < modules.cols(); j++) {
			for (int x = 0; x < scale; x++) {
				for (int y = 0; y < scale; y++) {
					if (modules(modules.cols() - 1 - j, i) == 0) {
						R(i*scale + x, j*scale + y) = 255;
						G(i*scale + x, j*scale + y) = 255;
						B(i*scale + x, j*scale + y) = 255;
					}
					else {
						R(i*scale + x, j*scale + y) = 0;
						G(i*scale + x, j*scale + y) = 0;
						B(i*scale + x, j*scale + y) = 0;
					}
					A(i*scale + x, j*scale + y) = 255;
				}
			}
		}
	}
	igl::png::writePNG(R, G, B, A, file);
}

/*
void qrcode::write_png(std::string file, Eigen::MatrixXi & modules,Eigen::MatrixXi &modules_c,int scale)
{
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
	R.resize((modules.rows())*scale, (modules.cols())*scale);
	G.resize((modules.rows())*scale, (modules.cols())*scale);
	B.resize((modules.rows())*scale, (modules.cols())*scale);
	A.resize((modules.rows())*scale, (modules.cols())*scale);
	for (int i = 0; i < modules.rows(); i++) {
		for (int j = 0; j < modules.cols(); j++) {
			for (int x = 0; x < scale; x++) {
				for (int y = 0; y < scale; y++) {
					if (modules(modules.cols() - 1 - j, i) == 0) {
						R(i*scale + x, j*scale + y) = 255;
						G(i*scale + x, j*scale + y) = 255;
						B(i*scale + x, j*scale + y) = 255;
					}
					else if(modules(modules.cols() - 1 - j, i) == 1&& modules_c(modules.cols() - 1 - j, i) == 0){
						R(i*scale + x, j*scale + y) = 255;
						G(i*scale + x, j*scale + y) = 0;
						B(i*scale + x, j*scale + y) = 0;
					}
					else if (modules(modules.cols() - 1 - j, i) == 1 && modules_c(modules.cols() - 1 - j, i) == 1) {
						R(i*scale + x, j*scale + y) = 0;
						G(i*scale + x, j*scale + y) = 0;
						B(i*scale + x, j*scale + y) = 0;
					}
					A(i*scale + x, j*scale + y) = 255;
				}
			}
		}
	}
	igl::png::writePNG(R, G, B, A, file);
}

void qrcode::write_png1(std::string file, Eigen::MatrixXi & modules, Eigen::MatrixXi &modules_c, int scale)
{
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
	R.resize((modules.rows())*scale, (modules.cols())*scale);
	G.resize((modules.rows())*scale, (modules.cols())*scale);
	B.resize((modules.rows())*scale, (modules.cols())*scale);
	A.resize((modules.rows())*scale, (modules.cols())*scale);
	for (int i = 0; i < modules.rows(); i++) {
		for (int j = 0; j < modules.cols(); j++) {
			for (int x = 0; x < scale; x++) {
				for (int y = 0; y < scale; y++) {
					if (modules(modules.cols() - 1 - j, i) == 0 && modules_c(modules.cols() - 1 - j, i) == 0) {
						R(i*scale + x, j*scale + y) = 255;
						G(i*scale + x, j*scale + y) = 255;
						B(i*scale + x, j*scale + y) = 255;
					}
					else if (modules(modules.cols() - 1 - j, i) == 0 && modules_c(modules.cols() - 1 - j, i) == 1) {
						R(i*scale + x, j*scale + y) = 0;
						G(i*scale + x, j*scale + y) = 255;
						B(i*scale + x, j*scale + y) = 0;
					}
					else if (modules(modules.cols() - 1 - j, i) == 1) {
						R(i*scale + x, j*scale + y) = 0;
						G(i*scale + x, j*scale + y) = 0;
						B(i*scale + x, j*scale + y) = 0;
					}
					A(i*scale + x, j*scale + y) = 255;
				}
			}
		}
	}
	igl::png::writePNG(R, G, B, A, file);
}

void qrcode::write_png(std::string file, Eigen::MatrixXi & modules)
{
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
	R.resize(modules.rows(), modules.cols());
	G.resize(modules.rows(), modules.cols());
	B.resize(modules.rows(), modules.cols());
	A.resize(modules.rows(), modules.cols());
	for (int y = 0; y < modules.rows();y++) {
		for (int x = 0; x < modules.cols(); x++) {
			R(y, x) = static_cast<unsigned char>(modules(modules.rows() - 1 - x, y));
			G(y, x) = static_cast<unsigned char>(modules(modules.rows() - 1 - x, y));
			B(y, x) = static_cast<unsigned char>(modules(modules.rows() - 1 - x, y));
			A(y, x) = 255;
		}
	}
	igl::png::writePNG(R, G, B, A, file);
}*/

void qrcode::write_png(std::string file, std::vector<std::vector<qrgen::Pixel>> pixels, Eigen::MatrixXi & modules, int scale)
{
	modules.resize(pixels.size() + 8, pixels.size() + 8);
	//Add white border
	for (int i = 0; i < pixels.size() + 8; i++) {
		for (int j = 0; j < 4; j++) {
			modules(i, j) = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < pixels.size() + 8; j++) {
			modules(i, j) = 0;
		}
	}
	for (int i = 4 + pixels.size(); i < pixels.size() + 8; i++) {
		for (int j = 4; j < pixels.size() + 8; j++) {
			modules(i, j) = 0;
		}
	}
	for (int i = 4; i < 4 + pixels.size(); i++) {
		for (int j = 4 + pixels.size(); j < pixels.size() + 8; j++) {
			modules(i, j) = 0;
		}
	}
    //Add data information
	for (int i = 4; i < 4 + pixels.size(); i++) {
		for (int j = 4; j < 4 + pixels.size(); j++) {
			modules(i, j) = pixels[i - 4][j - 4].getPixel();
		}
	}
	qrcode::write_png(file, modules, scale);
}

void qrcode::write_area(std::string file, Eigen::MatrixXd &area)
{
	/*Normalize*/
	float min = area.minCoeff();
	float max = area.maxCoeff();
	double depth = static_cast<double>(max - min);

	Eigen::MatrixXd m = (0.2 + (area.array() - static_cast<double>(min)) / depth*0.8).matrix();

	/*Write PNG*/
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
	R.resize(m.rows(), m.cols());
	G.resize(m.rows(), m.cols());
	B.resize(m.rows(), m.cols());
	A.resize(m.rows(), m.cols());
	for (int y = 0; y < m.rows(); y++) {
		for (int x = 0; x < m.cols(); x++) {

			if (area(m.rows() - 1 - x, y) != 0) {
				double c = m(m.rows() - 1 - x, y);
				double r, g, b;
				igl::jet(c, r, g, b);

				R(y, x) = static_cast<unsigned char>(r * 255);
				G(y, x) = static_cast<unsigned char>(g * 255);
				B(y, x) = static_cast<unsigned char>(b * 255);
				A(y, x) = 255;
			}
			else if (area(m.rows() - 1 - x, y) == 0) {
				R(y, x) = 255;
				G(y, x) = 255;
				B(y, x) = 255;
				A(y, x) = 255;
			}

		}
	}
	igl::png::writePNG(R, G, B, A, file);
}

void qrcode::write_area(std::string file, Eigen::MatrixXd &area, float min, float max, int scale)
{
	/*Normalize*/
	//float min = area.minCoeff();
	//float max = area.maxCoeff();

	double depth = static_cast<double>(max - min);

	Eigen::MatrixXd m = ((area.array() - static_cast<double>(min)) / depth).matrix();

	/*Write PNG*/
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
	R.resize(m.rows()*scale, m.cols()*scale);
	G.resize(m.rows()*scale, m.cols()*scale);
	B.resize(m.rows()*scale, m.cols()*scale);
	A.resize(m.rows()*scale, m.cols()*scale);
	for (int y = 0; y < m.rows(); y++) {
		for (int x = 0; x < m.cols(); x++) {
			for (int i = 0; i < scale; i++) {
				for (int j = 0; j < scale; j++) {
					if (area(m.rows() - 1 - x, y) != 0) {
						double c = m(m.rows() - 1 - x, y);
						double r, g, b;
						qrcode::jet(c, r, g, b);

						R(y*scale + i, x*scale + j) = static_cast<unsigned char>(r * 255);
						G(y*scale + i, x*scale + j) = static_cast<unsigned char>(g * 255);
						B(y*scale + i, x*scale + j) = static_cast<unsigned char>(b * 255);
						A(y*scale + i, x*scale + j) = 255;
					}
					else if (area(m.rows() - 1 - x, y) == 0) {
						R(y*scale + i, x*scale + j) = 255;
						G(y*scale + i, x*scale + j) = 255;
						B(y*scale + i, x*scale + j) = 255;
						A(y*scale + i, x*scale + j) = 255;
					}
				}
			}
		}
	}
	igl::png::writePNG(R, G, B, A, file);
}

void qrcode::write_area(std::string file, std::vector<std::vector<qrgen::Pixel>> pixels, Eigen::MatrixXd & area, float min, float max, int scale)
{
	double depth = static_cast<double>(max - min);

	Eigen::MatrixXd m = (0.2 + (area.array() - static_cast<double>(min)) / depth*0.8).matrix();

	/*Write PNG*/
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
	R.resize(m.rows()*scale, m.cols()*scale);
	G.resize(m.rows()*scale, m.cols()*scale);
	B.resize(m.rows()*scale, m.cols()*scale);
	A.resize(m.rows()*scale, m.cols()*scale);

	for (int y = 0; y < m.rows(); y++) {
		for (int x = 0; x < m.cols(); x++) {
			for (int i = 0; i < scale; i++) {
				for (int j = 0; j < scale; j++) {					

					if (area(m.rows() - 1 - x, y) != 0) {

						double c = m(m.rows() - 1 - x, y);
						double r, g, b;
						igl::jet(c, r, g, b);

						R(y*scale + i, x*scale + j) = static_cast<unsigned char>(r * 255);
						G(y*scale + i, x*scale + j) = static_cast<unsigned char>(g * 255);
						B(y*scale + i, x*scale + j) = static_cast<unsigned char>(b * 255);
						A(y*scale + i, x*scale + j) = 255;
					}
					else if (area(m.rows() - 1 - x, y) == 0) {
						R(y*scale + i, x*scale + j) = 255;
						G(y*scale + i, x*scale + j) = 255;
						B(y*scale + i, x*scale + j) = 255;
						A(y*scale + i, x*scale + j) = 255;
					}
				}
			}
		}
	}

	igl::png::writePNG(R, G, B, A, file);
}
