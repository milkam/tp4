/**
 * \file BorneFontaineTesteur.cpp
 * \brief Fichier de Test pour tester Borne Fontaine
 * \author Michel Tremblay
 * \date 2015-11-21
 */

#include "BorneFontaine.h"
#include <gtest/gtest.h>
#include <iostream>
using namespace tp;
/**
 * \class BorneFontaineValide
 * \brief Test fixture pour les méthodes de la classe BorneFontaine
 */
class BorneFontaineValide: public ::testing::Test
{
public:
	/**
	 * \brief Creation de l'objet pour la fixture
	 */
	BorneFontaineValide() :
		myBorneFontaine(193,"Sud","8800 24e Avenue",24.0,21.2,"Quebec","Myarrondo"),
		myBorneFontaine2(193,"Sud","8800 24e Avenue",24.0,21.2,"Quebec","Myarrondo"),
		myBorneFontaine3(193,"Sud","8800 24e Avenue",24.0,21.2,"Montreal","Myarrondo")
	{
	}
	/**
		 * \brief Creation de l'objet pour la fixture
		 */
	BorneFontaine myBorneFontaine;
	BorneFontaine myBorneFontaine2;
	BorneFontaine myBorneFontaine3;
};

/*
 * \test {Test de toutes les accesseur de la classe BorneFontaine (inclus ceux hétité de la classe Borne)
 *  Cas valide : toute les valeurs sont égual à ceux inséré dans la fixture
 *  Cas invalide : une ou plusieurs valeurs sont différente de ceux inséré dans la fixture}
 */
TEST_F(BorneFontaineValide,test_Accesseur)
{
	ASSERT_EQ(myBorneFontaine.reqId(), 193);
	ASSERT_EQ(myBorneFontaine.reqDirection(), "Sud");
	ASSERT_EQ(myBorneFontaine.reqNomTopographique(), "8800 24e Avenue");
	ASSERT_EQ(myBorneFontaine.reqLongitude(), 24.0);
	ASSERT_EQ(myBorneFontaine.reqLatitude(), 21.2);
	ASSERT_EQ(myBorneFontaine.reqVille(), "Quebec");
	ASSERT_EQ(myBorneFontaine.reqArrondissement(), "Myarrondo");
};

/*
 * \brief Test de l'assignateur de la classe BorneFontaine (hérité de la classe Borne)
 *	Cas valide : Nouveaux nom topographique est "Nouvelle Adresse"
 *  Cas invalide : Le nouvexu nom topographique n'est pas "Nouvelle Adresse"
 */
TEST_F(BorneFontaineValide,test_Assignateur)
{
	myBorneFontaine.asgNomTopographique("Nouvelle Adresse");
	ASSERT_NE(myBorneFontaine.reqNomTopographique(), "8800 24e Avenue");
	ASSERT_EQ(myBorneFontaine.reqNomTopographique(), "Nouvelle Adresse");
};

/*
 * \brief Test de la surcharge de l'opérateur =
 *	Cas valide : L'opérateur égual retourne true or false dépendant si les 2 objet sont identique ou pas
 *  Cas invalide : L'opérateur égual retourne toujours true ou false sans lien avec les valeur inséré.
 */
TEST_F(BorneFontaineValide, test_Overload_Operateur_Egual)
{
	ASSERT_TRUE(myBorneFontaine == myBorneFontaine2);
	ASSERT_FALSE(myBorneFontaine == myBorneFontaine3);
};

/*
 * \brief Test du constructeur BorneFontaine
 *	Cas valide : La BorneFontaine est bien créer et lance les exceptions lorsque nécessaire (Manque un champ ou une condition)
 *  Cas invalide : Une Exception est lancé lorsque non nécessaire, ou aucune exception n'est lancé lorsque nécessaire.
 */
TEST(BorneFontaine, testConstructeur)
{
	ASSERT_THROW(BorneFontaine(1,"Sud","8800 24e Avenue",24.0,21.2,"Quebec",""),ContratException);
	ASSERT_NO_THROW(BorneFontaine(1,"Sud","8800 24e Avenue",24.0,21.2,"Montreal",""));
	ASSERT_NO_THROW(BorneFontaine(1,"Sud","8800 24e Avenue",24.0,21.2,"Quebec","Ville Saint je sais pas"));
	ASSERT_THROW(BorneFontaine(1,"Nord-Ouest","8800 24e Avenue",24.0,21.2,"Quebec","Ville Saint je sais pas"),ContratException);
	ASSERT_THROW(BorneFontaine(1,"Sud","",24.0,21.2,"Quebec",""),ContratException);
	ASSERT_THROW(BorneFontaine(1,"Sud","8800 24e Avenue",0,21.2,"Quebec",""),ContratException);
	ASSERT_THROW(BorneFontaine(1,"Sud","8800 24e Avenue",24,0,"Quebec",""),ContratException);
	ASSERT_THROW(BorneFontaine(1,"Sud","8800 24e Avenue",24.0,21.2,"",""),ContratException);
};





