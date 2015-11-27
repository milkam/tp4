/**
 * \file Borne.h
 * \brief Interface de la classe Borne
 * \author Michel Tremblay
 * \date 2015-10-10
 */


#ifndef BORNE_H_
#define BORNE_H_
#include <string>
#include "ContratException.h"

namespace tp {

/**
 * \class Borne
 * \brief une classe qui permet de modéliser tous les types de bornes présents dans la ville de Québec.
 */
class Borne {
public:
	//Constructeur et destructeur
	Borne(	int p_idBorne,
			const std::string& p_direction,
			const std::string& p_nomTopographique,
			double p_longitude = 0,
			double p_latitude = 0);

	virtual ~Borne();

	//Methodes D'accès
	const int reqId() const;
	const std::string& reqDirection() const;
	const std::string& reqNomTopographique() const;
	const double reqLongitude() const;
	const double reqLatitude() const;

	//Méthode d'assignation
	void asgNomTopographique(const std::string& p_nomTopographique);

	//surcharge D'opérateur
	virtual bool operator==(const Borne& p_borne) const;

	//Méthode virtuel pure
	virtual std::string reqBorneFormate() const = 0;
	virtual Borne* clone() const = 0;



private:
	//Variables
	int m_idBorne; //Le numéro de la borne. Not-Null
	std::string m_direction; //Le côté du centre de chaussé ou l'intersection dans le cas t'un terre-plein.
	std::string m_nomTopographique; //Le nom topographique(générique,liaison,spécifique,direction) du centre de la chaussée.
	double m_longitude;
	double m_latitude;

	//Méthode utilitaire
	void verifieInvariant() const; //Theorie du contrat
};

} /* namespace Borne */

#endif /* BORNE_H_ */
