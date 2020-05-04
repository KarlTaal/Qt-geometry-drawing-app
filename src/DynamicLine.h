#ifndef DYNAMICLINE_H
#define DYNAMICLINE_H
#include <cmath>
/** @file */

/**
 * @brief Dünaamiline sirglõik.
 *
 * Viidatud tippudega sirglõik
 * @tparam T tipu tüüp.
 */
template<class T>
class DynamicLine {

public:
    ///Sirglõiku esimene tipp.
    T* p1;
    ///Sirglõiku teine tipp.
    T* p2;

    /**
     * @brief Konstruktor.
     *
     * Konstruktor viidatud tippudega sirglõigule.
     * @param v1 viit esimesele tipule (pointer)
     * @param v2 viit teisele tipule (pointer)
     */
	DynamicLine (T *v1, T *v2) {
		p1 = v1;
		p2 = v2;
	}

	/**
	 * @brief Koopiakonstruktor.
	 *
	 * Koopiakonstruktor viidatud tippudega sirglõigule.
	 * @param l Viidatud tippudega sirglõik.
	 */
	DynamicLine (const DynamicLine& l){
	    p1 = l.p1;
	    p2 = l.p2;
	}

	/**
	 * @brief Omistamiskäsk.
	 *
	 * Omistamiskäsk viidatud tippudega sirglõigule.
	 * @param l Viidatud tippudega sirglõik.
	 * @return Tagastab selle viidatud tippudega sirglõigu.
	 */
	DynamicLine& operator= (const DynamicLine& l){
	    p1 = l.p1;
	    p2 = l.p2;
	    return *this;
	}

	/**
	 * @brief Destruktor.
	 *
	 * Destruktor viidatud tippudega sirglõigule.
	 */
	~DynamicLine(){};
};

#endif // DYNAMICLINE_H
