//
//  RegisterComponents.cpp
//  EPet
//
//  Created by marina porkhunova on 14.09.2025.
//

#include "RegisterComponents.hpp"

#include "CommonComponents.hpp"
#include "SaveComponents.hpp"
#include "LoadComponents.hpp"

void RegisterComponents()
{
    GenerateLoadingFunction<Sorting>("Sorting", &Sorting::Load);
    GenerateSaveFunction<Sorting>("Sorting", &Sorting::Save);

    GenerateLoadingFunction<Transform>("Transform", &Transform::Load);
    GenerateSaveFunction<Transform>("Transform", &Transform::Save);

    GenerateLoadingFunction<Image>("Image", &Image::Load);
    GenerateSaveFunction<Image>("Image", &Image::Save);
}
