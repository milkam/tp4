/**
 * \file RegistreBorne.h
 * \brief
 * \author Michel Tremblay
 * \date 2015-11-22
 */

#ifndef REGISTREBORNE_H_
#define REGISTREBORNE_H_

#include "BorneStationnement.h"
#include "BorneFontaine.h"
#include <string>
#include <vector>

namespace tp
{

/**
 * \class RegistreBorne
 * \brief une classe qui permet de conserver les bornes dans un registre.
 */
class RegistreBorne
{
public:
	//Constructeur et destructeur
	RegistreBorne(const std::string& p_nomRegistreBorne);
	virtual ~RegistreBorne();

	//Methodes D'accès
	const std::string& reqNomRegistreBorne() const;
	const std::vector<Borne*>& reqVBornes() const;
	std::string reqRegistreBorneFormate() const;

	//Méthode Utilitaire
	void ajouteBorne(const Borne& p_Borne);



private:
	std::string m_nomRegistreBorne; //le Nom du registre
	std::vector<Borne*> m_vBornes; //vecteur qui contient toute les bornes

	//Méthode Virtuelle
	virtual RegistreBorne* clone() const;

	//Méthode Utilitaire
	bool BorneEstDejaPresente(const Borne& p_borne) const;
	void verifieInvariant() const; //Theorie du contrat

};

} /* namespace tp */

#endif /* REGISTREBORNE_H_ */
