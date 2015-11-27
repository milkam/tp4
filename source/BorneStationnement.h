/**
 * \file BorneStationnement.h
 * \brief
 * \author Michel Tremblay
 * \date 2015-11-21
 */

#ifndef BORNESTATIONNEMENT_H_
#define BORNESTATIONNEMENT_H_

#include "Borne.h"


namespace tp {

/**
 * \class BorneStationnement
 * \brief une classe qui permet de modéliser les bornes de type borne Stationnement.
 */
class BorneStationnement: public Borne {
public:
	//Constructeur destructeur
	BorneStationnement( int p_idBorne,
			const std::string& p_direction,
			const std::string& p_nomTopographique,
			double p_longitude,
			double p_latitude,
			const std::string& p_type,
			double p_lectureMetrique,
			int p_segmentRue,
			const std::string& p_numBorne,
			const std::string& p_coteRue);

	virtual ~BorneStationnement();

	//Méthodes d'accès
	const std::string& reqCoteRue() const;
	double reqLectureMetrique() const;
	const std::string& reqNumBorne() const;
	int reqSegmentRue() const;
	const std::string& reqType() const;

	//Méthode Virtuelle
	virtual std::string reqBorneFormate() const;
	virtual BorneStationnement* clone() const;

	//surcharge D'opérateur
	virtual bool operator==(const BorneStationnement& p_borneStationnement) const;


private:
	//Variables
	std::string m_type; //Le type de borne de stationnement, peut être <<stationnement>> ou <<paiement>>
	double m_lectureMetrique; //La distance mesurée à partie du début du tronçon dans le sens des numéros d'immeuble. Doit être > 0
	int m_segmentRue; // l'identifiant du segment de voie publique. Il doit être > 0
	std::string m_numBorne; //Le numéro de la borne. Il doit être non vide.
	std::string m_coteRue; //Le côté par rapport au centre de chaussée où est la borne. Doit correspondre à un point cardinal.

	//Méthode utilitaire
	void verifieInvariant() const; //Theorie du contrat
};

} /* namespace tp */

#endif /* BORNESTATIONNEMENT_H_ */
