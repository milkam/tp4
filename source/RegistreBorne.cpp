/**
 * \file RegistreBorne.cpp
 * \brief
 * \author Michel Tremblay
 * \date 2015-11-22
 */

#include "RegistreBorne.h"
#include <sstream>
#include <iostream>

using namespace std;

namespace tp
{

/**
 * \brief Constructeur de RegistreBorne
 * \param[in] p_nomRegistreBorne Le nom du registre de la borne, non null
 * \pre p_nomRegistreBorne non vide
 * \post vérification des attribut membre qu'ils contiennent tous des attributs valide
 * \return un objet RegistreBorne
 */
RegistreBorne::RegistreBorne(const std::string& p_nomRegistreBorne):
		m_nomRegistreBorne(p_nomRegistreBorne)
{
	PRECONDITION(!p_nomRegistreBorne.empty());
	POSTCONDITION(m_nomRegistreBorne == p_nomRegistreBorne);
	INVARIANTS();
}

RegistreBorne::~RegistreBorne()
{
}

void RegistreBorne::ajouteBorne(const Borne& p_Borne)
{
	if(!BorneEstDejaPresente(p_Borne))
	{
		m_vBornes.push_back(p_Borne.clone());
	}
	INVARIANTS();
}

string RegistreBorne::reqRegistreBorneFormate() const
{
	ostringstream os;
	os << "Registre : bornes de la ville de Québec 2015" << endl;
	for (unsigned int i = 0; i < m_vBornes.size(); i++)
	{
		os << m_vBornes[i]->reqBorneFormate() <<
				"-----------------------------------------------------------" << endl;
	}
	return os.str();
}

RegistreBorne* RegistreBorne::clone() const
{
	return NULL;
	INVARIANTS();
}

bool RegistreBorne::BorneEstDejaPresente(const Borne& p_borne) const
{
	bool presence = false;
	for (unsigned int i = 0; i < m_vBornes.size() && !presence; i++)
	{
		if(m_vBornes[i]->reqId() == p_borne.reqId())
		{
			presence = true;
		}
	}
	return presence;
	INVARIANTS();
}

const std::string& RegistreBorne::reqNomRegistreBorne() const
{
	return m_nomRegistreBorne;
}

const std::vector<Borne*>& RegistreBorne::reqVBornes() const
{
	return m_vBornes;
}

void RegistreBorne::verifieInvariant() const
{
	INVARIANT(!m_nomRegistreBorne.empty());
}

} /* namespace tp */


