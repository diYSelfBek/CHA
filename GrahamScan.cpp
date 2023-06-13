#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

// Function to find the anchor point (the point with the lowest y-coordinate)
Point findAnchorPoint(const vector<Point>& points) {
    Point anchor = points[0];
    for (const Point& p : points) {
        if (p.y < anchor.y || (p.y == anchor.y && p.x < anchor.x)) {
            anchor = p;
        }
    }
    return anchor;
}

// Function to calculate the orientation of three points
int orientation(const Point& p1, const Point& p2, const Point& p3) {
    int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    if (val == 0) {
        return 0;  // Collinear points
    } else if (val > 0) {
        return 1;  // Clockwise orientation
    } else {
        return -1; // Counterclockwise orientation
    }
}

// Comparator function for sorting points by polar angle with respect to the anchor point
bool compareByPolarAngle(const Point& p1, const Point& p2, const Point& anchor) {
    int o = orientation(anchor, p1, p2);
    if (o == 0) {
        // If two points have the same polar angle, the one closer to the anchor comes first
        return (p1.x * p1.x + p1.y * p1.y) < (p2.x * p2.x + p2.y * p2.y);
    }
    return o > 0;
}

// Points sorting by polar angle with respect to the anchor point
vector<Point> sortByPolarAngle(const vector<Point>& points, const Point& anchor) {
    vector<Point> sortedPoints = points;
    sort(sortedPoints.begin(), sortedPoints.end(), [&](const Point& p1, const Point& p2) {
        return compareByPolarAngle(p1, p2, anchor);
    });
    return sortedPoints;
}

vector<Point> grahamScan(const vector<Point>& points) {
    if (points.size() < 3) {
        // Not enough points to form a convex hull
        return {};
    }

    // Find the anchor point (point with the lowest y-coordinate)
    Point anchor = findAnchorPoint(points);

    // Sort points by their polar angle with respect to the anchor point
    vector<Point> sortedPoints = sortByPolarAngle(points, anchor);

    // Initialize the hull with the first two points in the sorted order
    vector<Point> hull;
    hull.push_back(sortedPoints[0]);
    hull.push_back(sortedPoints[1]);

    // Compute the remaining points of the convex hull
    for (int i = 2; i < sortedPoints.size(); i++) {
        // Check the orientation of the last two points and the current point
        while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull[hull.size() - 1], sortedPoints[i]) <= 0) {
            // Remove the last point from the hull if it does not make a counter-clockwise turn with the other two points
            hull.pop_back();
        }

        // Add the current point to the hull
        hull.push_back(sortedPoints[i]);
    }

    // Return the computed convex hull
    return hull;
}

int main() {
    vector<Point> points = {
        {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}
    };

    vector<Point> convexHull = grahamScan(points);

    cout << "Convex Hull:\n";
    for (const Point& p : convexHull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}