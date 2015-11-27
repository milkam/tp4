/**
 * \file BorneFontaine.h
 * \brief Implementation de la classe BorneFontaine
 * \author Michel Tremblay
 * \date 2015-11-21
 */


#ifndef BORNEFONTAINE_H_
#define BORNEFONTAINE_H_

#include "Borne.h"


namespace tp {

/**
 * \class BorneFontaine
 * \brief une classe qui permet de modéliser les bornes de type borne fontaine.
 */
class BorneFontaine: public Borne {
public:
	//Constructeur et destructeur
	BorneFontaine(int p_idBorne,
			const std::string& p_direction,
			const std::string& p_nomTopographique,
			double p_longitude,
			double p_latitude,
			const std::string& p_ville,
			const std::string& p_arrondissement);

	virtual ~BorneFontaine();

	//Methodes D'accès

	const std::string& reqVille() const;
	const std::string& reqArrondissement() const;


	//Virtuelle

	virtual BorneFontaine* clone() const;
	virtual std::string reqBorneFormate() const;

	//surcharge D'opérateur
	bool operator==(const BorneFontaine& p_borneFontaine) const;


private:
	//Variables
	std::string m_ville; //La ville de la borne
	std::string m_arrondissement; //L'arrondissement de la borne, qui est requis si la ville est <Quebec>

	//Méthode utilitaire
	void verifieInvariant() const; //Theorie du contrat
};

} /* namespace tp */

#endif /* BORNEFONTAINE_H_ */
