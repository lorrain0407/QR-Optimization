#include "jet.h"
void qrcode::jet(const double x_in, double & r, double & g, double & b)
{	
	if (x_in < 0)
	{
		r = 0.0;
		g = 0.0;
		b = 1.0;
	}
	else if (x_in >= 0.0&&x_in < 0.25)
	{
		r = 0.0;
		g = x_in / 0.25;
		b = 1.0;
	}
	else if (x_in >= 0.25&&x_in < 0.5)
	{
		r = 0.0;
		g = 1.0;
		b = 1.0 - (x_in - 0.25) / 0.25;
	}
	else if (x_in >= 0.5&&x_in < 0.75)
	{
		r = (x_in - 0.5) / 0.25;
		g = 1.0;
		b = 0.0;
	}
	else if (x_in >= 0.75&&x_in <= 1)
	{
		r = 1.0;
		g = 1.0 - (x_in - 0.75) / 0.25;
		b = 0.0;
	}
	else
	{
		r = 1.0;
		g = 0.0;
		b = 0.0;
	}
	// Only important if the number of colors is small. In which case the rest is
	// still wrong anyway
	// x = linspace(0,1,jj)' * (1-1/jj) + 1/jj;
	//
	/*const double rone = 0.8;
	const double gone = 1.0;
	const double bone = 1.0;
	double x = x_in;
	x = (x_in<0 ? 0 : (x>1 ? 1 : x));
	if (x<1. / 8.)
	{
	r = 0;
	g = 0;
	b = bone*(0.5 + (x) / (1. / 8.)*0.5);
	}
	else if (x<3. / 8.)
	{
	r = 0;
	g = gone*(x - 1. / 8.) / (3. / 8. - 1. / 8.);
	b = bone;
	}
	else if (x<5. / 8.)
	{
	r = rone*(x - 3. / 8.) / (5. / 8. - 3. / 8.);
	g = gone;
	b = (bone - (x - 3. / 8.) / (5. / 8. - 3. / 8.));
	}
	else if (x<7. / 8.)
	{
	r = rone;
	g = (gone - (x - 5. / 8.) / (7. / 8. - 5. / 8.));
	b = 0;
	}
	else
	{
	r = (rone - (x - 7. / 8.) / (1. - 7. / 8.)*0.5);
	g = 0;
	b = 0;
	}*/
}