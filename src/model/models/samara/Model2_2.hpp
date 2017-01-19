/**
 * @file model/models/samara/Model2_1.hpp
 * @author The Samara Development Team
 * See the AUTHORS file
 */

/*
 * Copyright (C) 2013-2017 Cirad http://www.cirad.fr
 * Copyright (C) 2013-2017 ULCO http://www.univ-littoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MODEL_MODELS_SAMARA_MODEL2_2_HPP
#define MODEL_MODELS_SAMARA_MODEL2_2_HPP

#include <model/models/ModelParameters.hpp>
#include <model/models/meteo/Meteo.hpp>
#include <model/models/samara/Model2_1.hpp>

#include <utils/DateTime.hpp>

namespace samara {

class Model2_2 : public Model2_1
{
public:
    Model2_2(const samara::AbstractModel* parent) : Model2_1(parent)
    { }

    virtual ~Model2_2()
    { }

    void compute(double t, bool update);
    void init(double t, const model::models::ModelParameters& parameters);

protected:
    void transplanting();
    void evalRespMaint();
    void evalRelPotLeafLength();
    void evolPlantTilNumTot();
    void evolMobiliTillerDeath();
    void evalSlaMitch();
    void evalRUE();
    void initParcelle();

    static double NullValue;
};

} // namespace samara

#endif
