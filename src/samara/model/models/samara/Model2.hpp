/**
 * @file samara/model/models/samara/Model2_1.hpp
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

#ifndef MODEL_MODELS_SAMARA_MODEL2_HPP
#define MODEL_MODELS_SAMARA_MODEL2_HPP

#include <samara/model/models/ModelParameters.hpp>
#include <samara/model/models/samara/SamaraModel.hpp>

#include <samara/utils/DateTime.hpp>

namespace samara {

class SamaraModel2 : public SamaraModel
{
public:
    SamaraModel2(const samara::AbstractModel* parent) : SamaraModel(parent)
    { }

    virtual ~SamaraModel2()
    { }

    void init(double t, const model::models::ModelParameters& parameters);

protected:
    void initParcelle();
    void transplanting();
    void evalDegreeDay();
    void evalDAF();
    void evalFTSW();
    void evalCstrPFactorFAO();
    void evolConsRes_Flood();
    void transplantingShock();
    void evolPlantTilNumTot();
    void evalDemandStructRoot();
    void evalDemandStructPanicle();
    void excessAssimilToRoot();
    void evalRuiss_FloodDyna();
    void evolRempliResRFE_RDE();
    void evolWaterLoggingUpland();
    void evalStressWaterLogging();
    void evolRempliMacropores();
    void plantSubmergence();

    static double NullValue;
};

} // namespace samara

#endif
