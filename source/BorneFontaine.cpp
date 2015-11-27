/**
 * \file BorneFontaine.cpp
 * \brief
 * \author Michel Tremblay
 * \date 2015-11-21
 */

#include "BorneFontaine.h"
#include <sstream>
#include <iostream>

using namespace std;
namespace tp {

/**
 * \brief Constructeur de BorneFontaine
 * \param[in] p_idBorne int Le numéro de la borne. Not-Null
 * \param[in] p_direction string Le côté du centre de chaussé ou l'intersection dans le cas t'un terre-plein.
 * \param[in] p_nomTopographique string Le nom topographique(générique,liaison,spécifique,direction) du centre de la chaussée.
 * \param[in] p_longitude double La longitude de la borne
 * \param[in] p_latitude double La latitude de la borne
 * \param[in] p_ville string Le nom de la ville Il doit être non vide
 * \param[in] p_arrondissement string L'arrondissement Il doit être non vide si la ville est Quebec
 * \pre p_direction doit être un point cardinal valide [Nord,Sud,Est,Ouest,"",null] (Par héritances)
 * \pre p_ville non vide
 * \pre p_arrondissement non vide si p_ville = Quebec
 * \post vérification des attribut membre qu'ils contiennent tous des attributs valide
  * \return un objet BorneFontaine
 */
BorneFontaine::BorneFontaine(int p_idBorne, const std::string& p_direction,
		const std::string& p_nomTopographique, double p_longitude,
		double p_latitude, const std::string& p_ville,
		const std::string& p_arrondissement)
			:Borne(p_idBorne,p_direction,p_nomTopographique,p_longitude,p_latitude),
			 m_ville(p_ville),
			 m_arrondissement(p_arrondissement){
	PRECONDITION(!p_ville.empty());
	PRECONDITION(!(p_ville == "Quebec" && p_arrondissement.empty()));
	POSTCONDITION(!m_ville.empty());
	POSTCONDITION(!(m_ville == "Quebec" && m_arrondissement.empty()));
	INVARIANTS();

}

/**
 * \brief Accesseur pour string m_ville
 * \return m_ville
 */
const string& BorneFontaine::reqVille() const
{
	return m_ville;
}

/**
 * \brief Accesseur pour string m_arrondissement
 * \return m_arrondissement
 */
const string& BorneFontaine::reqArrondissement() const
{
	return m_arrondissement;
}

/**
 * \brief Méthode pour cloner un objet BorneFontaine
  * \return un objet BorneFontaine
 */
BorneFontaine* BorneFontaine::clone() const
{
	return new BorneFontaine(*this); //Appel du constructeur copie
}

/**
 * \brief Méthode augmenté de la classe Borne.
 * \return une string formaté incluants les métriques spécifique pour les Bornes Fontaines.
 */
string BorneFontaine::reqBorneFormate() const
{
	ostringstream os;
	os << "Borne fontaine\n" <<
		"-----------------------------------------------------------" << endl <<
		Borne::reqBorneFormate() <<
		"Ville\t\t\t: " << m_ville << endl <<
		"Arrondissement\t\t: " << m_arrondissement << endl;
		return os.str();
}

/**
 * \brief Opérateur d'égalité. Si une seule propriété n'est pas idendique, les bornes ne sont pas identique.
 * \param[in] p_borneFontaine un objet de type BorneFontaine
 * \return boolean
 */
bool BorneFontaine::operator ==(const BorneFontaine& p_borneFontaine) const
{
		bool toreturn = true;
		if(!(Borne::operator ==(p_borneFontaine)))
		{
			toreturn = false;
		}
		else if (this->m_ville != p_borneFontaine.m_ville)
		{
			toreturn = false;
		}
		else if (m_arrondissement != p_borneFontaine.m_arrondissement)
		{
			toreturn = false;
		}
		return toreturn;
}

void BorneFontaine::verifieInvariant() const {
		INVARIANT(!m_ville.empty());
		INVARIANT(!(m_ville == "Quebec" && m_arrondissement.empty()));
}

BorneFontaine::~BorneFontaine() {
}

} /* namespace tp */


