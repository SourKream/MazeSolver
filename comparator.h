#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Point.h"

class mycomparison
{
	Point dest;
	public:
		mycomparison(Point *d)
		{
			dest.setRow(d->getRow());
			dest.setColumn(d->getColumn());
		}

		bool operator() (const Point& lhs, const Point& rhs) const
		{
			return (lhs.distanceFrom(dest) > rhs.distanceFrom(dest));
		}
};

#endif
