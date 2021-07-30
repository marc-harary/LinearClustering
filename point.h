class Point {
public:
    static int pointCount;
    float x, y;
    int hash_idx;
    Point(float, float);
    Point();
    float dist(const Point&);
    std::size_t hash() const;
    bool operator==(const Point&) const;
    friend std::ostream& operator<<(std::ostream&, const Point&);
};
