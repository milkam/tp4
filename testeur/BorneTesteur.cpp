/**
 * \file BorneTesteur.cpp
 * \brief Fichier de Test pour tester Borne
 * \author Michel Tremblay
 * \date 2015-11-24
 */

#include "Borne.h"
#include <gtest/gtest.h>
#include <iostream>
using namespace tp;


/**
 * \class BorneTesteurValide to use Abstract class Borne
 * \brief simple class to use Abstract class Borne
 */
class BorneTesteurValide: public Borne
{
public:
	BorneTesteurValide(int p_idBorne = 0, const std::string& p_direction = "",
				const std::string& p_nomTopographique = "", double p_longitude = 0.0,
				double p_latitude = 0.0):
				Borne(p_idBorne,p_direction,p_nomTopographique,p_longitude,p_latitude)
	{
	}
	virtual ~BorneTesteurValide(){}
	bool operator ==(const BorneTesteurValide& p_borne) const{
		return Borne::operator ==(p_borne);
	}
	BorneTesteurValide* clone() const
	{
		return new BorneTesteurValide(*this); //Appel du constructeur copie
	}
	std::string reqBorneFormate() const
	{
		return Borne::reqBorneFormate();
	}
};


/*
 * \Brief Test pour s'assurer que la classe borne est bien Abstraite
 *  Cas valide : On ne peut créer une borne seul.
 *  Cas invalide : Le borne est créer sans erreurs.
 */

class BorneValide: public ::testing::Test
{
public:

	/**
	 * \brief Creation de l'objet pour la fixture
	 */
	BorneValide() :
		myBorne(193,"Sud","8800 24e Avenue",24.0,21.2),
		myBorne2(193,"Sud","8800 24e Avenue",24.0,21.2)
	{
	}
	BorneTesteurValide myBorne;
	BorneTesteurValide myBorne2;
};

/**
 * \brief test des accesseur
 * Cas Valide : Toute les valeurs retourné sont ceux entré
 * Cas Invalide : une des valeur retourné n'est pas la bonne
 */
TEST_F(BorneValide, test_accesseur)
{
	ASSERT_EQ(myBorne.reqId(),193);
	ASSERT_EQ(myBorne.reqDirection(),"Sud");
	ASSERT_EQ(myBorne.reqNomTopographique(),"8800 24e Avenue");
	ASSERT_EQ(myBorne.reqLongitude(),24.0);
	ASSERT_EQ(myBorne.reqLatitude(),21.2);
};

/**
 * \brief test de l'assignateur de Borne
 * Cas Valide : La nouvelle adresse a bien été sauvegardé
 * Cas Invalide : La nouvelle adresse n'a pas été sauvé
 */
TEST_F(BorneValide, test_Assignateur)
{
	myBorne.asgNomTopographique("Nouvelle adresse");
	ASSERT_EQ(myBorne.reqNomTopographique(),"Nouvelle adresse");
};

/**
 * \brief test de l'operateur ==
 * Cas Valide : L'operateur fonctionne comme prévue
 * Cas Invalide : L'opérateur ne fait pas la différence entre une borne qui est pas pareil à l'autre
 */
TEST_F(BorneValide, test_OperateurSurcharge)
{
	ASSERT_TRUE(myBorne == myBorne2);
	myBorne.asgNomTopographique("Autre Adresse");
	ASSERT_FALSE(myBorne == myBorne2);
};

/*
 * \brief Test du constructeur Borne
 *	Cas valide : La Borne est bien créer et lance les exceptions lorsque nécessaire (Manque un champ ou une condition)
 *  Cas invalide : Une Exception est lancé lorsque non nécessaire, ou aucune exception n'est lancé lorsque nécessaire.
 */
TEST(BorneTesteurValide, test_Constructeur)
{
	ASSERT_NO_THROW(BorneTesteurValide myBorneTest(193,"Sud","8800 24e Avenue",24.0,21.2));
	ASSERT_NO_THROW(BorneTesteurValide myBorneTest1(193,"","8800 24e Avenue",24.0,21.2));
	ASSERT_NO_THROW(BorneTesteurValide myBorneTest2(193,"null","8800 24e Avenue",24.0,21.2));
	ASSERT_THROW(BorneTesteurValide myBorneTest3(193,"Nord-Ouest","8800 24e Avenue",24.0,21.2),ContratException);
	ASSERT_THROW(BorneTesteurValide myBorneTest3(193,"Nord-Ouest","8800 24e Avenue",0,21.2),ContratException);
	ASSERT_THROW(BorneTesteurValide myBorneTest3(193,"Nord-Ouest","8800 24e Avenue",23,0),ContratException);

};








