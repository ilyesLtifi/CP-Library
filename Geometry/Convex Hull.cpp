/**
 * This code generates the Convex Hull of a set of points
 * i.e. the smallest polygon that contains all the points(in the correct order)
 * in O(N*log(N))
*/

vector<Point> convexHull(vector<Point>&pnts) {
    if(size(pnts) == 1) return pnts;

    sort(begin(pnts), end(pnts), [](Point a, Point b) {
        return a.X < b.X || (a.X == b.X && a.Y < b.Y);
    });

    Point p1 = pnts[0];
    Point p2 = pnts.back();

    vector<Point> up, down;
    up.push_back(p1);
    down.push_back(p1);

    for (int i = 1; i < size(pnts); i++) {
        if (i == size(pnts) - 1 || cw(p1, pnts[i], p2)) {
            while (size(up) >= 2 && !cw(up[size(up)-2], up[size(up)-1], pnts[i])) up.pop_back();
            up.push_back(pnts[i]);
        }

        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(size(down) >= 2 && !ccw(down[size(down)-2], down[size(down)-1], pnts[i])) down.pop_back();
            down.push_back([pnts[i]);
        }
    }

    vector<Point> hull;
    for (int i = 0; i < (int)up.size(); i++) hull.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--) hull.push_back(down[i]);
    
    return hull;
}