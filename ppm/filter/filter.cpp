// filter.cpp : Defines the entry point for the console application.
//
//Karagiannis Stefanos 3150057
//Morfiadakis Emmanouil 3150112
#include "stdafx.h"
#include<iostream>
#include"FilterLinear.h"
#include"FilterGamma.h"
#include"FilterLaplace.h"
#include"Image.h"
#include<string>
using namespace std;
using namespace math;
void play(char** ar, int &i, Image& im) {
	if (strcmp(ar[i], "-f") && strcmp(ar[i], "–f")) exit(0);
	i++;
	if (!strcmp(ar[i], "linear")) {
		i++;
		Vec3<float>a(atof(ar[i]), atof(ar[i + 1]), atof(ar[i + 2]));
		i += 3;
		Vec3<float>c(atof(ar[i]), atof(ar[i + 1]), atof(ar[i + 2]));
		i += 3;
		FilterLinear fl(a, c);
		im = fl << im;

	}
	else if (!strcmp(ar[i], "gamma")) {
		i++;
		float y = atof(ar[i]);
		i++;
		FilterGamma fg(y);
		im = fg << im;

	}
	else if (!strcmp(ar[i], "blur")) {
		i++;
		int N = atoi(ar[i]);
		i++;
		FilterBlur fb(N);
		im = fb << im;
	}
	else if (!strcmp(ar[i], "laplace")) {
		i++;
		FilterLaplace fla;
		im = fla << im;
	}
	else {
		cout << "There is wrong in arguments";
		exit(0);
	}

}

int findHexoflastUSC(string x) {
	for (int i = x.length() - 1; i >= 0; i--)
		if (x[i] == '/')
			return i;
	return -1;
}

int main(int argc, char**argv)
{
	cout << "Loading";
	if (argc == 1)
		return 0;
	Image im;
	string fi2(argv[argc - 1]);
	int g = fi2.find(".") + 1;
	im.load(fi2.substr(0, g), fi2.substr(g));
	int i = 1;
	while (i < argc - 1) {
		play(argv, i, im);
	}

	int xq = findHexoflastUSC(fi2.substr(0, g));
	if (xq == -1)
		im.save("filtered_" + fi2.substr(0, g), fi2.substr(g));
	else {
		string last = fi2.substr(0, xq + 1) + "filtered_" + fi2.substr(xq + 1) + fi2.substr(g);
		im.save(last.substr(0, last.find(".") + 1), "ppm");
	}
	return 0;
}

