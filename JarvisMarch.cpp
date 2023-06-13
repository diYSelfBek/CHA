#include <iostream>
#include <vector>
using namespace std;

// point in 2D space
struct Point {
    int x, y;
};

// Function to determine the orientation of three points (clockwise, counterclockwise, or collinear)
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    
    if (val == 0)
        return 0; // collinear
    else if (val > 0)
        return 1; // clockwise
    else
        return -1; // counterclockwise
}

// Jarvis March algorithm to find the convex hull of a set of points
vector<Point> jarvisMarch(vector<Point>& points) {
    int n = points.size();
    
    // If the number of points is less than 3, then no convex hull can be formed
    if (n < 3)
        return {};
    
    vector<Point> hull;
    
    // Find the leftmost point to start the algorithm
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x)
            leftmost = i;
    }
    
    int p = leftmost, q;
    
    // Iterate until the first point is reached again
    do {
        hull.push_back(points[p]); // Add the current point to the convex hull
        q = (p + 1) % n; // Set q to the next point in the array
        
        // Find the next point with the smallest counterclockwise angle from the current point
        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == -1)
                q = i;
        }
        
        p = q; // Set p to the next point
    } while (p != leftmost);
    
    return hull; // Return the convex hull
}

int main() {
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    
    vector<Point> hull = jarvisMarch(points);
    
    cout << "Convex Hull:\n";
    for (auto& point : hull) {
        cout << "(" << point.x << ", " << point.y << ")\n";
    }
    
    return 0;
}