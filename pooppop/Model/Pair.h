#ifndef POOPPOP_MODEL_PAIR_H_
#define POOPPOP_MODEL_PAIR_H_

#include <utility>
#include "Piece.h"

namespace pooppop {
	namespace model {

		class Pair {
		public:
			enum class Orientation {
				HORIZONTAL = 0,
				VERTICAL
			};

			Pair();
			Pair(Piece*, Piece*);
			Pair(Piece*, Piece*, Orientation);
			inline Piece* GetFirst() { return pieces.first; }
			inline Piece* GetSecond() { return pieces.second; }
			inline Orientation GetOrientation() { return orientation; }

		private:
			std::pair<Piece*, Piece*> pieces;
			Orientation orientation;
		};
	}
}

#endif  // POOPPOP_MODEL_PAIR_H_