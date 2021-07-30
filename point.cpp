Point::Point(float x, float y) : x(x), y(y), hash_idx(pointCount) {
    pointCount++;
}

Point::Point() : x(0), y(0), hash_idx(pointCount) {
    pointCount++;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "{" << p.x << ", " << p.y << "}";
    return os;
}

float Point::dist(const Point& rhs) {
    return sqrt(pow(rhs.x-x, 2) + pow(rhs.y-y, 2));
}

bool Point::operator==(const Point& rhs) const {
    return x == rhs.x && y == rhs.y;
}

std::size_t Point::hash() const {
    long a, b, A, B, C;
    a = 100 * x;
    b = 100 * y;
    A = a >= 0 ? 2 * a : -2 * a - 1;
    B = b >= 0 ? 2 * b : -2 * b - 1;
    C = (A >= B ? A * A + A + B : A + B * B) / 2;
    return a < 0 && b < 0 || a >= 0 && b >= 0 ? C : -C - 1;
}

namespace std {
    template<> struct hash<Point> {
        std::size_t operator()(Point const& p) const noexcept {
            return p.hash();
        }
    };
}



int Point::pointCount = 0;
