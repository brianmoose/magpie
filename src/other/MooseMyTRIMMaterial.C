#include "MooseMyTRIMMaterial.h"

MooseMyTRIMMaterial::MooseMyTRIMMaterial(MyTRIM_NS::SimconfType * simconf) :
    MyTRIM_NS::MaterialBase(simconf, 0.0)
{
}

MyTRIM_NS::ElementBase *
MooseMyTRIMMaterial::getElement(unsigned int nn)
{
  // store the recoil element index in the tag field
  tag = nn;
  return _element[nn];
}

void
MooseMyTRIMMaterial::calculateDensity(Real site_volume)
{
  // sum up mass per lattice site
  _rho = 0.0;
  for (unsigned int i = 0; i < _element.size(); ++i)
    _rho += _element[i]->_t * _element[i]->_m;

  // compute density in amu/nm^3
  _rho /= site_volume;

  // convert _rho into g/cm^3 (1amu = 1.66054e-24g, 1nm^3 = 1e-21cm^3)
  _rho *= 1.66054e-3;
}