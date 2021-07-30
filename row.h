#define PRIME 105341

class Row {
public:
    static int rowCount;
    int hash_idx;
    std::list< std::shared_ptr<Point> > points;
    Point centroid;
    long size;

    Row(std::list< std::shared_ptr<Point> >, long, Point);
    Row();

    void add(std::shared_ptr<Point>);
    float cost() const;
    bool tooFar(const Point&, float) const;

    bool operator==(const Row&) const;
    friend std::ostream& operator<<(std::ostream&, const Row);
};
