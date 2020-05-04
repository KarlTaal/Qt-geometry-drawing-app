#ifndef POINT2_H
#define POINT2_H
#include <iostream>
using std::ostream;
/** @file */


/**
 * @brief Punkt kahemõõtmelisel tasandil.
 *
 * See klass kujutab punkti kahemõõtmelisel tasandil.
 * */
class Point2 {

public:
    ///Punkti x koordinaat.
	float x = 0;
    ///Punkti y koordinaat.
	float y = 0;

    /**
    * @brief Vaike konstruktor.
    *
    * Vaike konstruktor loob Point2 objekti, kus koordinaadid on (0, 0).
    * */
	Point2() = default;

    /**
    * @brief Point2 etteantud koordinaatidega konstruktor.
    *
    * Konstruktor loob Point2 objekti, kus koordinaadid on (nx, ny).
    * \param nx on float tüüpi argument x koordinaadiks.
    * \param ny on float tüüpi argument y koordinaadiks.
    * */
	Point2(float nx, float ny);

    /**
    * @brief Kahe punkti kauguse leidmine.
    *
    * See funktsioon tagastab kahe punkti kauguse etteantud punktist.
    * \param v on Point2 tüüpi argument.
    * \returns Kaugus punktist v
    * */
	float distanceFrom(Point2 v);
	
	friend ostream& operator << (ostream& valja, Point2 v); /*!< Kirjutab väljundvoogu punkti koordinaadid kujul (nx, ny).*/
};

#endif 
