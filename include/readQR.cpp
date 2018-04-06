#include "readQR.h"

int qrcode::readData(const std::string file, Eigen::MatrixXi & D)
{
	int cols, rows, n;
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic>R, G, B, A;
	unsigned char *data = stbi_load(file.c_str(), &cols, &rows, &n, 4);
	if (data == NULL) {
		return false;
	}
	R.resize(cols, rows);
	G.resize(cols, rows);
	B.resize(cols, rows);
	A.resize(cols, rows);
	D.resize(cols, rows);
	for (unsigned i = 0; i < rows; ++i) {
		for (unsigned j = 0; j < cols; ++j) {
			R(i, j) = data[4 * (i + cols * j) + 0];
			G(i, j) = data[4 * (i + cols * j) + 1];
			B(i, j) = data[4 * (i + cols * j) + 2];
			A(i, j) = data[4 * (i + cols * j) + 3];
		}
	}

	stbi_image_free(data);
	Eigen::MatrixXd temp = 0.3*R.cast<double>() + 0.59*G.cast<double>() + 0.11*B.cast<double>();
	for (int i = 0; i < temp.rows(); i++) {
		for (int j = 0; j < temp.cols(); j++) {
			D(i, j) = (temp(i, j) > 0) ? 0 : 1;
		}
	}
	R.resize(0, 0);
	G.resize(0, 0);
	B.resize(0, 0);
	A.resize(0, 0);
	return D.rows();
}

//qrcode::QRinfo qrcode::readQR(Engine *engine,std::string & file_name)
//{
//
//	QRinfo qrinfo;
//	/*Analyze QR configuration*/
//
//	int level = 0, mask = -1, border = 4, scale = 1;
//	char text[4096];
//
//	const char* file = file_name.c_str();
//	FILE *in = fopen(file, "r");
//
//	if (in == (FILE*)NULL) {
//		assert(false && "Cannot open the qrcode info file!!!");
//	}
//	else {
//		fscanf(in, "%d %d %d %d\n", &level, &mask, &border, &scale);
//		fscanf(in, "%s\n", &text);
//		fclose(in);
//		std::string info = text;
//
//		qrinfo.scale = scale;
//		qrinfo.border = border;
//		/*Generate origin QR code */
//		qrgen::Bits bits;
//		qrgen::Version *version = qrgen::getMinVersion(info, static_cast<qrgen::LEVEL>(level), bits);
//
//		/*Property and code word initialization*/
//		std::vector<qrgen::CodeWord> codeword(bits.getSize() / 8, qrgen::CodeWord());
//		qrinfo.codewodrs = codeword;
//		std::cout << bits.getSize() / 8 << std::endl;
//		/*Block property*/
//		qrgen::VerInfo verinfo = qrgen::Version::VERSION_INFOS[version->getVersion()];
//		int num_block = verinfo.lvlInfos[level].num_of_block;
//		int num_check_byte = verinfo.lvlInfos[level].cbytes_pre_block;
//
//		int num_block_l = verinfo.lvlInfos[qrgen::LEVEL::L].num_of_block;
//		int num_check_byte_l = verinfo.lvlInfos[qrgen::LEVEL::L].cbytes_pre_block;
//
//		const int PRIORITY_MAX = floor(static_cast<double>(num_check_byte*num_block - num_check_byte_l*num_block_l) / (2*num_block));
//		qrinfo.num_of_check_byte = num_check_byte;
//		std::cout << "PRIORITY_MAX:" << num_check_byte << num_check_byte_l<< std::endl;
//		std::vector<int> Block_Priority(num_block, PRIORITY_MAX);
//
//		qrinfo.block_propertys = Block_Priority;
//
//		/*Pixel Property*/
//		std::vector <std::vector < qrgen::PixelProperty>> Pixel_Property;
//		float area = std::numeric_limits<float>::max();
//
//		if (mask == -1) {
//			for (int i = 0; i < 8; i++) {
//
//				Eigen::MatrixXi modules, functions;
//
//				Pixel_Property.clear();
//				std::vector<std::vector<qrgen::Pixel>> pixels = encode(bits, version, static_cast<qrgen::LEVEL>(level), new qrgen::Mask(i));
//
//				pixel_to_matrix(pixels, border, modules, functions);
//				visualarea(engine, modules, functions, Pixel_Property);
//
//				int count = 0;
//				double temp_area = 0;
//
//				for (int y = 0; y < Pixel_Property.size(); y++) {
//					for (int x = 0; x < Pixel_Property.size(); x++) {
//						if (Pixel_Property[y][x].area > 0) count++;
//						temp_area += Pixel_Property[y][x].area;
//					}
//				}
//
//				temp_area /= count;
//
//				if (temp_area < area) {
//					area = temp_area;
//					qrinfo.pixels = pixels;
//					qrinfo.pixel_propertys = Pixel_Property;
//				}
//
//			}
//		}
//		else {
//			Pixel_Property.clear();
//			std::vector<std::vector<qrgen::Pixel>> &pixels = encode(bits, version, static_cast<qrgen::LEVEL>(level), new qrgen::Mask(mask));
//
//			Eigen::MatrixXi modules, functions;
//
//			pixel_to_matrix(pixels, border, modules, functions);
//			visualarea(engine, modules, functions, Pixel_Property);
//
//			qrinfo.pixels = pixels;
//			qrinfo.pixel_propertys = Pixel_Property;
//
//		}
//	}
//
//	return qrinfo;
//}
