/**
 * \file BorneStationnementTesteur.cpp
 * \brief Fichier de Test pour tester Borne Stationnement
 * \author Michel Tremblay
 * \date 2015-11-21
 */

#include "BorneStationnement.h"
#include <gtest/gtest.h>
using namespace tp;

/**
 * \class BorneStationnementValide
 * \brief Test fixture pour les méthodes de la classe BorneStationnement
 */
class BorneStationnementValide: public ::testing::Test
{
public:
	/**
	 * \brief Creation de l'objet pour la fixture
	 */
	BorneStationnementValide() :
		myBorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498","Nord"),
		myBorneStationnement2(193,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498","Nord"),
		myBorneStationnement3(193,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498","Sud")
	{
	}
	/**
	* \brief Creation de l'objet pour la fixture
	*/
	BorneStationnement myBorneStationnement;
	BorneStationnement myBorneStationnement2;
	BorneStationnement myBorneStationnement3;
};

/*
 * \briefTest de toutes les accesseur de la classe BorneStationnement (inclus ceux hétité de la classe Borne)
 *  Cas valide : toute les valeurs sont égual à ceux inséré dans la fixture
 *  Cas invalide : une ou plusieurs valeurs sont différente de ceux inséré dans la fixture
 */
TEST_F(BorneStationnementValide,test_Accesseur)
{
	ASSERT_EQ(myBorneStationnement.reqId(), 193);
	ASSERT_EQ(myBorneStationnement.reqDirection(), "Sud");
	ASSERT_EQ(myBorneStationnement.reqNomTopographique(), "8800 24e Avenue");
	ASSERT_EQ(myBorneStationnement.reqLongitude(), 24.0);
	ASSERT_EQ(myBorneStationnement.reqLatitude(), 21.2);
	ASSERT_EQ(myBorneStationnement.reqType(), "stationnement");
	ASSERT_EQ(myBorneStationnement.reqLectureMetrique(), 1234.3);
	ASSERT_EQ(myBorneStationnement.reqSegmentRue(), 387);
	ASSERT_EQ(myBorneStationnement.reqNumBorne(), "498");
	ASSERT_EQ(myBorneStationnement.reqCoteRue(), "Nord");
};

/*
 * \brief Test de la surcharge de l'opérateur =
 *	Cas valide : L'opérateur égual retourne true or false dépendant si les 2 objet sont identique ou pas
 *  Cas invalide : L'opérateur égual retourne toujours true ou false sans lien avec les valeur inséré.
 */
TEST_F(BorneStationnementValide, test_Overload_Operateur_Egual)
{
	ASSERT_TRUE(myBorneStationnement == myBorneStationnement2);
	ASSERT_FALSE(myBorneStationnement == myBorneStationnement3);
};

/*
 * \brief Test du constructeur BorneFontaine
 *	Cas valide : La BorneFontaine est bien créer et lance les exceptions lorsque nécessaire (Manque un champ ou une condition)
 *  Cas invalide : Une Exception est lancé lorsque non nécessaire, ou aucune exception n'est lancé lorsque nécessaire.
 */
TEST(BorneStationnement, testConstructeur)
{
	ASSERT_NO_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"paiement",1234.3,387,"498","Sud"));
	ASSERT_NO_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498","Sud"));
	ASSERT_NO_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498","Nord"));
	ASSERT_NO_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498","Est"));
	ASSERT_NO_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498","Ouest"));
	ASSERT_NO_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498","null"));
	ASSERT_NO_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498",""));
	ASSERT_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"autreNom",24.0,0,"498","Sud"),ContratException);
	ASSERT_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"autreNom",0,387,"498","Sud"),ContratException);
	ASSERT_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"autreNom",24.0,387,"","Sud"),ContratException);
	ASSERT_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"autreNom",24.0,387,"","Sud2"),ContratException);
	ASSERT_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"autreNom",24.0,387,"","Nord-Ouest"),ContratException);
	ASSERT_THROW(BorneStationnement(193,"Sud","8800 24e Avenue",24.0,21.2,"autreNom",24.0,387,"","Ailleur"),ContratException);
};





