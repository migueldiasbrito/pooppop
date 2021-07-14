#include "Pair.h"

namespace model = ::pooppop::model;

model::Pair::Pair() {

}

model::Pair::Pair(Piece* piece1, Piece* piece2) {
	pieces.first = piece1;
	pieces.second = piece2;
}

model::Pair::Pair(Piece* piece1, Piece* piece2, Orientation orientation) {
	pieces.first = piece1;
	pieces.second = piece2;
	this->orientation = orientation;
}
