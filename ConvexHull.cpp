// Caleb Catt
// Convex Hull with Jarvis's March multiple times

/*
	The program works by creating 100 random points between 0-100.
	Then These points are passed to convexHull where traversal starts from the left most (least x) point and traverses CCW using orientation.
	The points found are added to the hull vector, while the toRemove vector keeps track of the index of where the points were located in the points vector
	After the first layer is created, the points are removed from the points vector and convexHull is called recursively.

*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <time.h>
using namespace std;

struct Point
{
	int x, y;
};

// 0 --> p, q and r are in line
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // in line
	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}

void convexHull(vector<Point> points, int n, ofstream& myfile)
{
	// There must be at least 3 points 
	if (n < 3) return;

	vector<Point> hull;
	vector<int> toRemove;


	// Least x point
	int l = 0;
	for (int i = 1; i < n; i++)
		if (points[i].x < points[l].x)
			l = i;

	// Start from leftmost point, keep moving counterclockwise 
	int p = l, q;
	do
	{
		hull.push_back(points[p]);
		toRemove.push_back(p);

		q = (p + 1) % n;
		for (int i = 0; i < n; i++)
		{
			if (orientation(points[p], points[i], points[q]) == 2)
				q = i;
		}
		p = q;

	} while (p != l); 

	std::sort(toRemove.begin(), toRemove.end(), greater<int>());

	for (int i = 0; i < hull.size(); i++) {
		myfile << hull[i].x << " " << hull[i].y << " ";
		cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
		points.erase(points.begin() + toRemove[i]);
	}
	cout << "\n \n \n";
	myfile << "\n";
	convexHull(points, points.size(), myfile);
	myfile.close();
}

int main()
{
	unsigned seed = time(0);
	srand(seed);
	int v1, v2;
	vector<Point> points;
	for (int i = 0; i < 100; i++) {
		v1 = rand() % 100;
		v2 = rand() % 100;
		points.push_back({ v1, v2 });
	}
	int n = points.size();
	ofstream myfile;
	myfile.open("points.txt");
	convexHull(points, n, myfile);
	return 0;
}
