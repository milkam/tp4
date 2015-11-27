/*
 * validationFormat.h
 *
 *  Created on: 2015-09-26
 *      Author: mitre319
 *      Name: Michel Tremblay
 */

#ifndef VALIDATIONFORMAT_H_
#define VALIDATIONFORMAT_H_

namespace util
{
/**
 * \brief un fichier d'utilitaire de validation
 */
bool valideLigneGEOJSON (std::string& p_ligne, std::ostringstream& p_parametres);
bool valideLigneCVS (std::string& p_ligne, std::ostringstream& p_parametres);
bool validerGeom (const std::string& p_geom);
bool validerFloat(const std::string& number);
bool validerPointCardinal(const std::string& p_cardinalite);

} /* namespace util */

#endif /* VALIDATIONFORMAT_H_ */

