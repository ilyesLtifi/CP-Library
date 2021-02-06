/**
* A geometry helper namespace for Point/Vector operations
* It also includes segments/lines/circles/polygons algorithms and queries
*/

namespace Geo{
	const float EPS = 1e-16L, PI = acos(-1.0L);
	bool EQ(float a, float b){return fabs(a-b) < EPS;}
	bool LT(float a, float b){return fabs(a-b) > EPS && a < b;}
	bool GT(float a, float b){return fabs(a-b) > EPS && a > b;}
	#define LTE(a,b) (!GT(a,b))
	#define GTE(a,b) (!LT(a,b))
	#define Vector Point
	struct Point {
		float X, Y;
		Point(){}
		Point(float _X, float _Y): X(_X), Y(_Y){}
		bool operator==(const Point& oth) { return EQ(X, oth.X) && EQ(Y, oth.Y); }
		bool operator!=(const Point& oth) { return !EQ(X, oth.X) || !EQ(Y, oth.Y); }
		Point operator+(const Point& oth) { return Point( X + oth.X, Y + oth.Y ); }
		Point operator-(const Point& oth) { return Point( X - oth.X, Y - oth.Y ); }
		float operator*(const Point& oth) { return X * oth.X + Y * oth.Y; }
		float operator%(const Point& oth) { return X * oth.Y - Y * oth.X; }
		Point operator*(float f) { return Point( X * f, Y * f ); }
		Point operator/(float f) { return Point( X / f, Y / f ); }
	};
	struct Line{
		float a, b, c; Point p1, p2;
		Line(Point _p1, Point _p2) { p1 = _p1; p2 = _p2; a = p1.Y - p2.Y; b = p2.X - p1.X; c = p1.X*p2.Y - p2.X*p1.Y; }
	};
	float norm(Vector v) { return sqrtl(v.X*v.X + v.Y*v.Y); }
	float norm2(Vector v) { return v.X*v.X + v.Y*v.Y; }
	Vector perp(Vector v) { return Vector(v.Y, -v.X); }
	bool ccw(Point a, Point b, Point c) { return GTE((a-b)%(a-c), 0); }
	float angle(Vector v) { float ang = atan2(v.Y, v.X); return LT(ang, 0) ? ang+2*PI : ang; }
	Vector rotate(Vector v, float ang) { return Point(v.X * cos(ang) - v.Y * sin(ang), v.X * sin(ang) + v.Y * cos(ang)); } // returns vector v rotated 'ang' radians ccw around the origin
	bool insideLine(Point p, Point a, Point b){ return EQ((p-a)%(p-b), 0); }
	bool insideSegment(Point p, Point a, Point b) { return insideLine(p,a,b) && LTE((p-a)*(p-b), 0); }
	float distLine(Point p, Point a, Point b){ return fabs((p-a) % (b-a)) / norm(b-a); }
	float distSegment(Point p, Point a, Point b){
		if(LTE((p-a) * (b-a), 0)) return norm(p-a);
		if(LTE((p-b) * (a-b), 0)) return norm(p-b);
		return distLine(p, a, b);
	}
	int windingNumber(Point p, const vector<Point> &polygon) {
		int wn = 0;
		for(int i = 0; i < size(polygon); ++i) {
			Point a = polygon[i], b = polygon[(i+1)%size(polygon)];
			if (LTE(a.Y, p.Y) && LT(p.Y, b.Y) && ccw(a, b, p)) ++wn;
			if (LTE(b.Y, p.Y) && LT(p.Y, a.Y) && !ccw(a, b, p)) --wn;
		}
		return wn;
	}
	bool insidePolygon(Point p, const vector<Point> &polygon) { return windingNumber(p, polygon) != 0; }
	float minSegmentDist(Point a, Vector va, Point b, Vector vb){       // at instant t (in [0;1]) point a will be a + va*t and b will be b + vb*t
		if(va == vb) return norm(a - b);
		float t = -(Vector(a - b) * Vector(va - vb)) / norm2(va - vb);
		if(LT(t, 0.0L)) t = 0.0L;
		if(GT(t, 1.0L)) t = 1.0L;
		return norm((a + va*t) - (b + vb*t));
	}
	bool intersectLines(Point a, Point b, Point c, Point d, Point&ans) {
		float A1 = b.Y - a.Y, B1 = a.X - b.X, C1 = A1 * a.X + B1 * a.Y;
		float A2 = d.Y - c.Y, B2 = c.X - d.X, C2 = A2 * c.X + B2 * c.Y;
		float determinant = A1 * B2 - A2 * B1;
		if(EQ(determinant, 0)) return false;   // parallel
		ans = Point((B2 * C1 - B1 * C2) /determinant, (A1 * C2 - A2 * C1) /determinant);
		return true;
	}
	Point getCircleCenter(Point& a, Point& b, Point& c){  // 3 NON COLINEAR POINTS
		Point ab = (a + b) * 0.5L;
		Point ab2 = ab + perp(b - a);
		Point bc = (b + c) * 0.5L;
		Point bc2 = bc + perp(c - b);
		Point ans;
		if(!intersectLines(ab, ab2, bc, bc2, ans)) return Point(INFLL, INFLL);
		return ans;
	}
	pair<Point,float> minEnclosingCircle(vector<Point>& pnts){            // O(n^4)
		Point c; float r = INFLL;
		for(int i=0; i<size(pnts); ++i) for(int j=i+1; j<size(pnts); ++j){
			Point tmpC = (pnts[i] + pnts[j]) * 0.5L;
			float tmpR = 0.0L;
			for(int ind=0; ind<size(pnts); ++ind) tmpR = max(tmpR, norm(tmpC - pnts[ind]));
			if(LT(tmpR,r)) r = tmpR, c = tmpC;
		}
		for(int i=0; i<size(pnts); ++i) for(int j=i+1; j<size(pnts); ++j) for(int k=j+1; k<size(pnts); ++k){
			Point tmpC = getCircleCenter(pnts[i], pnts[j], pnts[k]);
			float tmpR = 0.0L;
			for(int ind=0; ind<size(pnts); ++ind) tmpR = max(tmpR, norm(tmpC - pnts[ind]));
			if(LT(tmpR,r)) r = tmpR, c = tmpC;
		}
		return {c, r};
	}
} using namespace Geo;
