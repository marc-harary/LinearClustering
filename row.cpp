Row::Row(std::list< std::shared_ptr<Point> > points, long size, Point centroid) :
    points(points),
    size(size),
    centroid(centroid),
    hash_idx(rowCount) {
    rowCount++;     
}


Row::Row() : points(), size(), centroid(), hash_idx(rowCount) {
    rowCount++;
}


void Row::add(std::shared_ptr<Point> point) {
    points.push_back(point);
    size++;
    centroid.x += point->x / size;
    centroid.y += point->y / size;
}


float Row::cost() const {
    float xBar, yBar;
    xBar = yBar = 0;
    for (auto it = points.begin(); it != points.end(); it++) {
        xBar += (*it)->x;
        yBar += (*it)->y;
    }
    xBar /= size;
    yBar /= size;

    std::list<float> xDeltas, yDeltas;
    for (auto it = points.begin(); it != points.end(); it++) {
        xDeltas.push_back((*it)->x - xBar);
        yDeltas.push_back((*it)->y - yBar);
    }

    auto itX = xDeltas.begin();
    auto itY = yDeltas.begin();
    float clusterEpsilon, variance, covariance, x2;
    clusterEpsilon = covariance = variance = 0;
    for (; itX != xDeltas.end() && itY != yDeltas.end(); itX++, itY++) {
        x2 = pow(*itX, 2);
        covariance += *itX * *itY;
        variance += x2;
        clusterEpsilon += sqrt(x2 + pow(*itY, 2));
    }

    float alpha, beta, linearEpsilon, yHat;
    beta = variance == 0 ? 0 : covariance / variance;
    alpha = yBar - beta*xBar;
    linearEpsilon = 0;
    for (auto it = points.begin(); it != points.end(); it++) {
        yHat = alpha + beta*(*it)->x;
        linearEpsilon += pow((*it)->y - yHat, 2);
    }

    return (clusterEpsilon + linearEpsilon) / size;
}


bool Row::tooFar(const Point& point, float maxDist) const {
    if (size == 0) {
        return false;
    }
    float dist = sqrt(pow(point.x-centroid.x,2) + pow(point.y-centroid.y,2));
    return dist > maxDist;
}


bool Row::operator==(const Row& rhs) const {
    if (size != rhs.size) {
        return false;
    }
    auto itL = points.begin();
    auto itR = rhs.points.begin();
    for (; itL != points.end(); itL++, itR++) {
        if (*itL != *itR) {
            return false;
        }
    }
    return true;
}


std::ostream& operator<<(std::ostream& os, const Row& r) {
    os << "{";
    if (r.size > 0) {
        os << *r.points.front();
    }
    if (r.size > 1) {
        // std::list<Point>::iterator it = r.points.begin();
        auto it = r.points.begin();
        it++;
        for ( ; it != r.points.end(); it++) {
            os << ",\n " << **it;
        }
    }
    os << "}";
    return os;
}


namespace std {
    template<> struct hash<Row> {
        std::size_t operator()(Row const& r) const noexcept {
            ulong long out, partition;
            out = 0;
            partition = PRIME / r.size;
            auto it = r.points.begin();
            int i = 0;
            for ( ; it != r.points.end(); i++, it++) {
                out += (*it)->hash() * partition * i;
            }
            return out % PRIME;
        }
    };
}


int Row::rowCount = 0;
