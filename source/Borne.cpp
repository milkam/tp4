/**
 * \file Borne.cpp
 * \brief Implementation de la classe Borne
 * \author Michel Tremblay
 * \date 2015-10-10
 */

#include "Borne.h"
#include <sstream>
#include <cassert>
#include <stdexcept>
#include "validationFormat.h"

using namespace std;
namespace tp
{

/**
 * \brief Constructeur de Borne
 * \param[in] p_idBorne int Le numéro de la borne.
 * \param[in] p_direction string Le côté du centre de chaussé ou l'intersection dans le cas t'un terre-plein.
 * \param[in] p_nomTopographique string Le nom topographique(générique,liaison,spécifique,direction) du centre de la chaussée.
 * \param[in] p_longitude double La longitude de la borne defaut de 0
 * \param[in] p_latitude double La latitude de la borne defaut de 0
 * \pre p_idBorne doit être non vide
 * \pre p_direction doit être un point cardinal valide [Nord,Sud,Est,Ouest,"",null]
 * \pre p_nomTopographique doit être non vide
 * \post vérification que tout les attribute nécessaire contienne des valeurs valides
 * \return un objet Borne
 */
Borne::Borne(int p_idBorne, const std::string& p_direction,
		const std::string& p_nomTopographique, double p_longitude,
		double p_latitude):
				m_idBorne(p_idBorne), m_direction(p_direction),
				m_nomTopographique(p_nomTopographique), m_longitude(p_longitude),
				m_latitude(p_latitude){
	PRECONDITION(p_idBorne > 0)
	PRECONDITION(util::validerPointCardinal(p_direction));
	PRECONDITION(!p_nomTopographique.empty());
	POSTCONDITION(m_idBorne > 0)
	POSTCONDITION(!m_nomTopographique.empty());
	POSTCONDITION(util::validerPointCardinal(m_direction));
	INVARIANTS();
}

/**
 * \brief Accesseur pour int m_idBorne
 * \return m_idBorne
 */
const int Borne::reqId() const {
	return m_idBorne;
}


/**
 * \brief Accesseur pour string m_direction
 * \return m_direction
 */
const string& Borne::reqDirection() const
{
	return m_direction;
}


/**
 * \brief Accesseur pour string m_nomTopographique
 * \return m_nomTopographique
 */
const string& Borne::reqNomTopographique() const
{
	return m_nomTopographique;
}

/**
 * \brief Accesseur pour double m_longitude
 * \return m_longitude
 */
const double Borne::reqLongitude() const
{
	return m_longitude;
}

/**
 * \brief Accesseur pour double m_latitude
 * \return m_latitude
 */
const double Borne::reqLatitude() const
{
	return m_latitude;
}

/**
 * \brief Accesseur pour string de Borne formatté
 * \return borneFormate
 */
string Borne::reqBorneFormate() const
{
	ostringstream os;
	os << "Identifiant de la borne\t: " << m_idBorne << endl <<
			"Direction\t\t: " << ((m_direction.length() > 0) ? m_direction : "Empty") << endl <<
			"Nom topographique\t: " << ((m_nomTopographique.length() > 0) ? m_nomTopographique : "Empty") << endl <<
			"Longitude\t\t: " << ((m_longitude > 0) ? m_longitude : 0) << endl <<
			"Latitude\t\t: " << ((m_latitude > 0) ? m_latitude : 0) << endl;
	return os.str();
}


/**
 * \brief Mutateur pour NomTopographique, modifie m_nomTopographique
 * \param[in] p_nomTopographique Le nom topographique(générique,liaison,spécifique,direction) du centre de la chaussée.
 * \pre nouveau Nom Topographique doit être non vide
 * \post vérifie que l'attribut m_nomTopographique contient le nouveau nom courant.
 */
void Borne::asgNomTopographique(const std::string& p_nomTopographique)
{
	PRECONDITION(!p_nomTopographique.empty())
	m_nomTopographique = p_nomTopographique;
	POSTCONDITION(m_nomTopographique == p_nomTopographique)
	INVARIANTS();
}


/**
 * \brief Opérateur d'égalité. Si une seule propriété n'est pas idendique, les bornes ne sont pas identique.
 * \param[in] p_borne un objet de type Borne
 * \return boolean
 */
bool Borne::operator ==(const Borne& p_borne) const
{
	bool toreturn = true;
	if (m_idBorne != p_borne.m_idBorne)
	{
		toreturn = false;
	}
	else if (!(m_direction == p_borne.reqDirection()))
	{
		toreturn = false;
	}
	else if (!(m_nomTopographique == p_borne.reqNomTopographique()))
	{
		toreturn = false;
	}
	else if (m_latitude != p_borne.m_latitude){
		toreturn = false;
	}
	else if (m_longitude != p_borne.m_longitude){
		toreturn = false;
	}
	return toreturn;
}
void Borne::verifieInvariant() const
{
	INVARIANT(m_idBorne > 0);
	INVARIANT(util::validerPointCardinal(m_direction));
	INVARIANT(!m_nomTopographique.empty());
}

Borne::~Borne() {
}


} /* namespace Borne */

