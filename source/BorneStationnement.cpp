/**
 * \file BorneStationnement.cpp
 * \brief
 * \author Michel Tremblay
 * \date 2015-11-21
 */

#include "BorneStationnement.h"
#include <iostream>
#include <sstream>
#include "validationFormat.h"

using namespace std;

namespace tp
{

/**
 * \brief Constructeur de Borne de Stationnement
 * \param[in] p_idBorne int Le numéro de la borne. Not-Null
 * \param[in] p_direction string Le côté du centre de chaussé ou l'intersection dans le cas t'un terre-plein.
 * \param[in] p_nomTopographique string Le nom topographique(générique,liaison,spécifique,direction) du centre de la chaussée.
 * \param[in] p_longitude double La longitude de la borne
 * \param[in] p_latitude double La latitude de la borne
 * \param[in] p_type Le type de borne de stationnement, peut être "stationnement" ou "paiement"
 * \param[in] p_lectureMetrique La distance mesurée à partie du début du tronçon dans le sens des numéros d'immeuble. Doit être > 0
 * \param[in] p_segmentRue L'identifiant du segment de voie publique. Il doit être > 0
 * \param[in] p_numBorne Le numéro de la borne. Il doit être non vide.
 * \param[in] p_coteRue Le côté par rapport au centre de chaussée où est la borne. Doit correspondre à un point cardinal.
 * \pre p_direction doit être un point cardinal valide [Nord,Sud,Est,Ouest,"",null] (Par héritances)
 * \pre p_type = stationnement ou paiement
 * \pre p_lectureMetrique > 0
 * \pre p_segmentRue > 0
 * \pre p_numBorne non vide
 * \pre p_coteRue Un point cartinal valide [Nord,Sud,Est,Ouest,"",null]
 * \post vérification des attribut membre qu'ils contiennent tous des attributs valide
 * \return un objet BorneStationnement
 */
BorneStationnement::BorneStationnement(int p_idBorne,
		const std::string& p_direction, const std::string& p_nomTopographique,
		double p_longitude, double p_latitude, const std::string& p_type,
		double p_lectureMetrique, int p_segmentRue,
		const std::string& p_numBorne, const std::string& p_coteRue) :
		Borne(p_idBorne, p_direction, p_nomTopographique, p_longitude,
				p_latitude),m_type(p_type), m_lectureMetrique(p_lectureMetrique), m_segmentRue(
				p_segmentRue), m_numBorne(p_numBorne), m_coteRue(p_coteRue)
{
	PRECONDITION(p_type == "stationnement" || p_type == "paiement");
	PRECONDITION(p_lectureMetrique > 0);
	PRECONDITION(p_segmentRue > 0);
	PRECONDITION(!p_numBorne.empty());
	PRECONDITION(util::validerPointCardinal(p_coteRue));
	POSTCONDITION(m_type == "stationnement" || m_type == "paiement");
	POSTCONDITION(m_lectureMetrique > 0);
	POSTCONDITION(m_segmentRue > 0);
	POSTCONDITION(!m_numBorne.empty());
	//POSTCONDITION(util::validerPointCardinal(m_coteRue));
	INVARIANTS();
}

BorneStationnement::~BorneStationnement()
{
}

/**
 * \brief Accesseur pour m_coteRue
 * \return m_coteRue
 */
const std::string& BorneStationnement::reqCoteRue() const
{
	return m_coteRue;
}
/**
 * \brief Accesseur pour m_lectureMetrique
 * \return m_lectureMetrique
 */
double BorneStationnement::reqLectureMetrique() const
{
	return m_lectureMetrique;
}
/**
 * \brief Accesseur pour m_numBorne
 * \return m_numBorne
 */
const std::string& BorneStationnement::reqNumBorne() const
{
	return m_numBorne;
}

/**
 * \brief Accesseur pour m_segmentRue
 * \return m_segmentRue
 */
int BorneStationnement::reqSegmentRue() const
{
	return m_segmentRue;
}
/**
 * \brief Accesseur pour m_type
 * \return m_type
 */
const std::string& BorneStationnement::reqType() const
{
	return m_type;
}
/**
 * \brief Méthode augmenté de la classe Borne.
 * \return une string formaté incluants les métriques spécifique pour les Bornes de Stationnement.
 */
std::string BorneStationnement::reqBorneFormate() const
{
	ostringstream os;
	os << "Borne de stationnement\n"
			<< "-----------------------------------------------------------"
			<< endl << Borne::reqBorneFormate() << "Distance mesuree\t: "
			<< m_lectureMetrique << endl << "Segment de rue\t\t: " << m_segmentRue
			<< endl << "Numero de la borne\t: " << m_numBorne << endl
			<< "Cote de la rue\t\t: " << m_coteRue << endl;
	return os.str();
}
/**
 * \brief Méthode pour cloner un objet BorneStationnement
  * \return un objet BorneFontaine
 */
BorneStationnement* BorneStationnement::clone() const
{
	return new BorneStationnement(*this); //Appel du constructeur copie
}

/**
 * \brief Opérateur d'égalité. Si une seule propriété n'est pas idendique, les bornes ne sont pas identique.
 * \param[in] p_borneStationnement un objet de type BorneStationnement
 * \return boolean
 */
bool BorneStationnement::operator ==(const BorneStationnement& p_borneStationnement) const
{
	bool toreturn = true;
	if(!(Borne::operator ==(p_borneStationnement)))
	{
				toreturn = false;
	}
	else if (m_type != p_borneStationnement.m_type)
	{
		toreturn = false;
	}
	else if (m_lectureMetrique != p_borneStationnement.m_lectureMetrique)
	{
		toreturn = false;
	}
	else if (m_segmentRue != p_borneStationnement.m_segmentRue)
	{
		toreturn = false;
	}
	else if (m_numBorne != p_borneStationnement.m_numBorne)
	{
		toreturn = false;
	}
	else if (m_coteRue != p_borneStationnement.m_coteRue)
	{
		toreturn = false;
	}
	return toreturn;
}

void BorneStationnement::verifieInvariant() const
{
	INVARIANT(m_type == "stationnement" || m_type == "paiement");
	INVARIANT(m_lectureMetrique > 0);
	INVARIANT(m_segmentRue > 0);
	INVARIANT(!m_numBorne.empty());
	//INVARIANT(util::validerPointCardinal(m_coteRue));
}

} /* namespace tp */


