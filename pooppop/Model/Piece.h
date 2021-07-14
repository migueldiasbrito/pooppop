#ifndef POOPPOP_MODEL_PIECE_H_
#define POOPPOP_MODEL_PIECE_H_

namespace pooppop {
	namespace model {

		class Piece {

		public:
			inline Piece(int color) {
				this->color = color;
			}

			inline int GetColor() {
				return color;
			}

		private:
			int color;
		};

	}
}

#endif  // POOPPOP_MODEL_PIECE_H_