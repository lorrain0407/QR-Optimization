#include "VisualArea.h"

//void qrcode::visualarea(Engine * engine, Eigen::MatrixXi & modules, Eigen::MatrixXi & functions, std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys)
//{
//	int size = modules.rows();
//
//	Eigen::MatrixXi label;
//	qrcode::bwlabel(engine, modules, 4, label);
//	std::vector<Eigen::MatrixXi> bounds;
//	qrcode::bwbound(label, bounds);
//	assert(!(bounds.size() != label.maxCoeff()) && "label error!!!");
//
//	pixel_propertys.resize(size);
//	for (int i = 0; i < size; i++) pixel_propertys[i].resize(size);
//	for (int y = 0; y < size - 1; y++) {
//		for (int x = 0; x < size - 1; x++) {
//			if (modules(y, x) > 0) {
//				std::vector<Eigen::Vector2d> bound;
//				qrcode::raw_to_visible_polygon(Eigen::RowVector2d(y + 0.5, x + 0.5), bounds[label(y, x) - 1], 1, size, bound);
//
//				boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> poly;
//				for (int i = 0; i < bound.size(); i++) 	poly.outer().emplace_back(bound[i](0), bound[i](1));
//				pixel_propertys[y][x].area = boost::geometry::area(poly);
//				
//			}
//		}
//	}
//}

void qrcode::visualarea(Engine * engine, Eigen::MatrixXi & modules, Eigen::MatrixXi & label, std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys)
{
	int size = modules.rows();

	qrcode::bwlabel(engine, modules, 4, label);
	std::vector<Eigen::MatrixXi> bounds;
	qrcode::bwbound(label, bounds);
	assert(!(bounds.size() != label.maxCoeff()) && "label error!!!");

	pixel_propertys.resize(size);
	for (int i = 0; i < size; i++) pixel_propertys[i].resize(size);
	for (int y = 0; y < size - 1; y++) {
		for (int x = 0; x < size - 1; x++) {
			if (modules(y, x) > 0) {
				std::vector<Eigen::Vector2d> bound;
				qrcode::raw_to_visible_polygon(Eigen::RowVector2d(y + 0.5, x + 0.5), bounds[label(y, x) - 1], 1, size, bound);
				
				// bound to triangle, triangulate and sum each area of triangles
				Eigen::MatrixXd V1;   // coordinate x, y
				Eigen::MatrixXi E1;
				V1.resize(bound.size(), 2);
				E1.resize(bound.size(), 2);
				for (int i = 0; i < bound.size(); i++) {					                 
					V1.row(i) = bound[i].transpose();
					E1.row(i) << i, (i + 1) % bound.size();							
				}
				//std::cout << "V1: " << V1 << std::endl << "E1: " << E1 << std::endl;

				Eigen::MatrixXi H(1, 2);
				H << -1, -1;
				//std::cout << "H: " << H << std::endl;
				Eigen::MatrixXd V;
				Eigen::MatrixXi	F;
				igl::triangle::triangulate(V1, E1, H, "a0.005q", V, F);
				//std::cout << "V" << V << std::endl;
				//std::cout << "F" << F << std::endl;
				pixel_propertys[y][x].area = qrcode::triArea(V, F);
				//std::cout << "area: " << pixel_propertys[y][x].area << std::endl;
				V1.resize(0, 0);
				E1.resize(0, 0);
				H.resize(0, 0);
				V.resize(0, 0);
				F.resize(0, 0);
				/*boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> poly;
				for (int i = 0; i < bound.size(); i++) 	poly.outer().emplace_back(bound[i](0), bound[i](1));
				pixel_propertys[y][x].area = boost::geometry::area(poly);*/
			}						
		}
	}			
}

void qrcode::visualarea(Engine * engine, Eigen::MatrixXi & modules, Eigen::MatrixXi & label, Eigen::MatrixXd & area)
{
	int size = modules.rows();

	qrcode::bwlabel(engine, modules, 4, label);
	std::vector<Eigen::MatrixXi> bounds;
	qrcode::bwbound(label, bounds);
	assert(!(bounds.size() != label.maxCoeff()) && "label error!!!");

	area.setZero(modules.rows(),modules.cols());
	for (int y = 0; y < size - 1; y++) {
		for (int x = 0; x < size - 1; x++) {
			if (modules(y, x) > 0) {
				std::vector<Eigen::Vector2d> bound;
				qrcode::raw_to_visible_polygon(Eigen::RowVector2d(y + 0.5, x + 0.5), bounds[label(y, x) - 1], 1, size, bound);

				// bound to triangle, triangulate and sum each area of triangles
				Eigen::MatrixXd V1;   // coordinate x, y
				Eigen::MatrixXi E1;
				V1.resize(bound.size(), 2);
				E1.resize(bound.size(), 2);
				for (int i = 0; i < bound.size(); i++) {
					V1.row(i) = bound[i].transpose();
					E1.row(i) << i, (i + 1) % bound.size();
				}
				//std::cout << "V1: " << V1 << std::endl << "E1: " << E1 << std::endl;

				Eigen::MatrixXi H(1, 2);
				H << -1, -1;
				//std::cout << "H: " << H << std::endl;
				Eigen::MatrixXd V;
				Eigen::MatrixXi	F;
				igl::triangle::triangulate(V1, E1, H, "a0.005q", V, F);
				//std::cout << "V" << V << std::endl;
				//std::cout << "F" << F << std::endl;
				area(y,x) = qrcode::triArea(V, F);
				//std::cout << "area: " << pixel_propertys[y][x].area << std::endl;
				V1.resize(0, 0);
				E1.resize(0, 0);
				H.resize(0, 0);
				V.resize(0, 0);
				F.resize(0, 0);
				/*boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> poly;
				for (int i = 0; i < bound.size(); i++) 	poly.outer().emplace_back(bound[i](0), bound[i](1));
				pixel_propertys[y][x].area = boost::geometry::area(poly);*/
			}
		}
	}
}

void qrcode::visualarea(Engine * engine, Eigen::MatrixXi & modules, Eigen::MatrixXi & label, std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys, Eigen::MatrixXd & area)
{
	area.resize(modules.rows(), modules.cols());
	qrcode::visualarea(engine, modules, label, pixel_propertys);
	for (int i = 0; i < modules.rows(); i++) {
		for (int j = 0; j < modules.cols(); j++) {
			area(i, j) = pixel_propertys[i][j].area;
		}
	}
	//cout << area << endl;
}

double qrcode::triArea(Eigen::MatrixXd &V, Eigen::MatrixXi &F) {
	double area = 0;
	for (int i = 0; i < F.rows(); i++) {
		// A line is too navie...
		int a = F(i, 0);
		int b = F(i, 1);
		int c = F(i, 2);
		Eigen::Vector3d A, B, C;
		A << V(a, 0), V(a, 1), 0;
		B << V(b, 0), V(b, 1), 0;
		C << V(c, 0), V(c, 1), 0;
		area += (C - A).cross(C - B).norm() / 2;
	}
	return area;
}

void qrcode::averageArea(std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys, Eigen::MatrixXi & label, std::vector<int>& num, std::vector<double>& averageArea)
{
	averageArea.resize(num.size());
	for (int i = 0; i < averageArea.size(); i++) {
		for (int j = 0; j < label.rows(); j++) {
			for (int k = 0; k < label.cols(); k++) {
				if (label(j, k) == i) {
					averageArea[i] += pixel_propertys[j][k].area;
				}
			}
		}
		averageArea[i] /= num[i];
	}

	/*cout << "aaaa:" << averageArea.size() << endl;
	for (int i = 0; i < averageArea.size(); i++) {
		cout << averageArea[i] << endl;
	}*/
}

void qrcode::averageArea(std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys, Eigen::MatrixXi & label, std::vector<int>& num, Eigen::MatrixXd & averageArea, Eigen::MatrixXd & averageAreaSort, Eigen::MatrixXd & I)
{
	averageArea.resize(num.size(),2);
	for (int i = 0; i < averageArea.rows(); i++) {
		averageArea(i, 0) = i;
		for (int j = 0; j < label.rows(); j++) {
			for (int k = 0; k < label.cols(); k++) {
				if (label(j, k) == i) {
					averageArea(i, 1) += pixel_propertys[j][k].area;
				}
			}
		}
		averageArea(i,1) /= num[i];
	}
	
	I.resize(num.size(), 2);
	averageAreaSort.resize(num.size(), 2);
	igl::sort(averageArea, 1, false, averageAreaSort, I);
}

void qrcode::averageArea(Eigen::MatrixXd & area, Eigen::MatrixXi & label, std::vector<int>& num, Eigen::MatrixXd & averageArea, Eigen::MatrixXd & averageAreaSort, Eigen::MatrixXd & I)
{
	averageArea.setZero(num.size(), 2);
	for (int i = 0; i < averageArea.rows(); i++) {
		averageArea(i, 0) = i;
		for (int j = 0; j < label.rows(); j++) {
			for (int k = 0; k < label.cols(); k++) {
				if (label(j, k) == i) {
					averageArea(i, 1) += area(j, k);
				}
			}
		}
		if (averageArea(i, 1) == 0) {
			averageArea(i, 1) = 0;
		}
		else {
			averageArea(i, 1) /= num[i];
		}
	}		

	averageAreaSort.resize(num.size(), 2);
	I.resize(num.size(), 2);
	igl::sort(averageArea, 1, false, averageAreaSort, I);
}

void qrcode::averageArea(Eigen::MatrixXd & area, Eigen::MatrixXi & label, std::vector<int>& num, Eigen::MatrixXd & averageArea, Eigen::MatrixXd & averageAreaSort)
{
	averageArea.setZero(num.size(), 2);
	std::vector<Eigen::Vector2d> temp;
	for (int i = 0; i < averageArea.rows(); i++) {
		averageArea(i, 0) = i;
		for (int j = 0; j < label.rows(); j++) {
			for (int k = 0; k < label.cols(); k++) {
				if (label(j, k) == i) {
					averageArea(i, 1) += area(j, k);
				}
			}
		}
		if (averageArea(i, 1) == 0) {
			averageArea(i, 1) = 0;
		}
		else {
			averageArea(i, 1) /= num[i];
		}
		temp.emplace_back(i, averageArea(i, 1));
	}

	std::stable_sort(temp.begin(), temp.end(), [](Eigen::Vector2d v1, Eigen::Vector2d v2) {return v1(1) > v2(1); });
	Eigen::MatrixXd averageAreaSort1;
	averageAreaSort1.resize(num.size(), 2);
	for (int i = 0; i < num.size(); i++) averageAreaSort1.row(i) = temp[i].transpose();
	averageAreaSort.resize(num.size(), 3);
	for (int i = 0; i < num.size(); i++) {
		averageAreaSort.row(i) << i, averageAreaSort1(i, 0), averageAreaSort1(i, 1);
	}
}

void qrcode::averageArea(Eigen::MatrixXd & area, Eigen::MatrixXi & label, std::vector<int>& num, Eigen::MatrixXd & averageAreaSort)
{
	Eigen::MatrixXd averageArea;
	averageArea.setZero(num.size(), 2);
	std::vector<Eigen::Vector2d> temp;
	for (int i = 0; i < averageArea.rows(); i++) {
		averageArea(i, 0) = i;
		for (int j = 0; j < label.rows(); j++) {
			for (int k = 0; k < label.cols(); k++) {
				if (label(j, k) == i) {
					averageArea(i, 1) += area(j, k);
				}
			}
		}
		if (averageArea(i, 1) == 0) {
			averageArea(i, 1) = 0;
		}
		else {
			averageArea(i, 1) /= num[i];
		}
		temp.emplace_back(i, averageArea(i, 1));
	}
	//std::cout << "averageArea:" << std::endl << averageArea << std::endl;

	std::stable_sort(temp.begin(), temp.end(), [](Eigen::Vector2d v1, Eigen::Vector2d v2) {return v1(1) > v2(1); });
	Eigen::MatrixXd averageAreaSort1;
	averageAreaSort1.resize(num.size(), 2);
	for (int i = 0; i < num.size(); i++) averageAreaSort1.row(i) = temp[i].transpose();
	temp.clear();
	averageAreaSort.resize(num.size(), 3);
	for (int i = 0; i < num.size(); i++) {
		averageAreaSort.row(i) << i, averageAreaSort1(i, 0), averageAreaSort1(i, 1);
	}

	//std::cout << "averageAreaSort:" << std::endl << averageAreaSort << std::endl;

}
//void qrcode::visualarea(Engine * engine, Eigen::MatrixXi & modules, Eigen::MatrixXi & label, int label_num, std::vector<std::vector<qrgen::PixelProperty>>& pixel_propertys)
//{
//	int size = modules.rows();
//
//	qrcode::bwlabel(engine, modules, 4, label,label_num);
//	std::vector<Eigen::MatrixXi> bounds;
//	qrcode::bwbound(label, bounds);
//	assert(!(bounds.size() != label.maxCoeff()) && "label error!!!");
//
//	pixel_propertys.resize(size);
//	for (int i = 0; i < size; i++) pixel_propertys[i].resize(size);
//	for (int y = 0; y < size - 1; y++) {
//		for (int x = 0; x < size - 1; x++) {
//			if (modules(y, x) > 0) {
//				std::vector<Eigen::Vector2d> bound;
//				qrcode::raw_to_visible_polygon(Eigen::RowVector2d(y + 0.5, x + 0.5), bounds[label(y, x) - 1], 1, size, bound);
//
//				boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> poly;
//				for (int i = 0; i < bound.size(); i++) 	poly.outer().emplace_back(bound[i](0), bound[i](1));
//				pixel_propertys[y][x].area = boost::geometry::area(poly);
//
//			}
//		}
//	}
//}