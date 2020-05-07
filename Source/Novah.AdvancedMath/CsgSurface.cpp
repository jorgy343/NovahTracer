#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

enum class IntersectionState : unsigned char
{
    BothOut = 0x0,
    LeftIn = 0x1,
    RightIn = 0x2,
    BothIn = 0x3
};

CsgSurface::CsgSurface(const Surface* leftSurface, const Surface* rightSurface, CsgOperation operation)
    : _leftSurface(leftSurface), _rightSurface(rightSurface), _operation(operation)
{

}

const Surface* CsgSurface::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    std::vector<IntersectionData> intersections;

    _leftSurface->IntersectRay(ray, &intersections);
    _rightSurface->IntersectRay(ray, &intersections);

    std::sort(intersections.begin(), intersections.end(), [](const IntersectionData& left, const IntersectionData& right)
    {
        return left.GetDistance() < right.GetDistance();
    });

    IntersectionState previousState = IntersectionState::BothOut;
    IntersectionState currentState = IntersectionState::BothOut;

    for (int i = 0; i < intersections.size(); ++i)
    {
        const IntersectionData& intersection = intersections[i];

        // Save the current state as the previous state.
        previousState = currentState;

        // Configure the new current state.
        if (intersection.GetCollisionSurface() == _leftSurface)
            currentState = (IntersectionState)(((unsigned char)currentState & (unsigned char)IntersectionState::RightIn) | (~(unsigned char)currentState & (unsigned char)IntersectionState::LeftIn));

        if (intersection.GetCollisionSurface() == _rightSurface)
            currentState = (IntersectionState)(((unsigned char)currentState & (unsigned char)IntersectionState::LeftIn) | (~(unsigned char)currentState & (unsigned char)IntersectionState::RightIn));

        // If the next intersection is close to the current intersection, merge the two intersections.
        if (i + 1 < intersections.size())
        {
            const IntersectionData& nextIntersection = intersections[i + 1];
            if (fabs(intersection.GetDistance() - nextIntersection.GetDistance()) < Epsilon)
                continue;
        }

        // Perform the boolean operation.
        switch (_operation)
        {
        case CsgOperation::Union:
            *intersectionData = intersection;

            intersectionData->SetCollisionSurface(this);
            //intersectionData->SetDetailedSurface(intersection.GetCollisionSurface());

            return this;

        case CsgOperation::Intersection:
            if (currentState == IntersectionState::BothIn)
            {
                *intersectionData = intersection;

                intersectionData->SetCollisionSurface(this);
                //intersectionData->SetDetailedSurface(intersection.GetCollisionSurface());

                return this;
            }
            break;

        case CsgOperation::Difference:
            if (currentState == IntersectionState::LeftIn)
            {
                *intersectionData = intersection;

                if (intersectionData->GetCollisionSurface() == _rightSurface)
                    intersectionData->SetNormal(-intersectionData->GetNormal());

                intersectionData->SetCollisionSurface(this);
                //intersectionData->SetDetailedSurface(intersection.GetCollisionSurface());

                return this;
            }
            break;
        }
    }

    return nullptr;
}

const Surface* CsgSurface::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    std::vector<IntersectionData> intersections;

    _leftSurface->IntersectRay(ray, &intersections);
    _rightSurface->IntersectRay(ray, &intersections);

    std::sort(intersections.begin(), intersections.end(), [](const IntersectionData& left, const IntersectionData& right)
    {
        return left.GetDistance() < right.GetDistance();
    });

    IntersectionState previousState = IntersectionState::BothOut;
    IntersectionState currentState = IntersectionState::BothOut;

    for (int i = 0; i < intersections.size(); ++i)
    {
        const IntersectionData& intersection = intersections[i];

        // Save the current state as the previous state.
        previousState = currentState;

        // Configure the new current state.
        if (intersection.GetCollisionSurface() == _leftSurface)
            currentState = (IntersectionState)(((unsigned char)currentState & (unsigned char)IntersectionState::RightIn) | (~(unsigned char)currentState & (unsigned char)IntersectionState::LeftIn));

        if (intersection.GetCollisionSurface() == _rightSurface)
            currentState = (IntersectionState)(((unsigned char)currentState & (unsigned char)IntersectionState::LeftIn) | (~(unsigned char)currentState & (unsigned char)IntersectionState::RightIn));

        // If the next intersection is close to the current intersection, merge the two intersections.
        if (i + 1 < intersections.size())
        {
            const IntersectionData& nextIntersection = intersections[i + 1];
            if (fabs(intersection.GetDistance() - nextIntersection.GetDistance()) < Epsilon)
                continue;
        }

        // Perform the boolean operation.
        switch (_operation)
        {
        case CsgOperation::Union:
            if (previousState == IntersectionState::BothOut && (currentState == IntersectionState::LeftIn || currentState == IntersectionState::RightIn))
            {
                IntersectionData temp = intersection;
                temp.SetCollisionSurface(this);
                //temp.SetDetailedSurface(intersection.GetCollisionSurface());

                intersectionData->push_back(temp);
            }
            else if ((previousState == IntersectionState::LeftIn || previousState == IntersectionState::RightIn || previousState == IntersectionState::BothIn) && currentState == IntersectionState::BothOut)
            {
                IntersectionData temp = intersection;
                temp.SetCollisionSurface(this);
                //temp.SetDetailedSurface(intersection.GetCollisionSurface());

                intersectionData->push_back(temp);
            }
            break;

        case CsgOperation::Intersection:
            if (previousState != IntersectionState::BothIn && currentState == IntersectionState::BothIn)
            {
                IntersectionData temp = intersection;
                temp.SetCollisionSurface(this);
                //temp.SetDetailedSurface(intersection.GetCollisionSurface());

                intersectionData->push_back(temp);
            }
            else if (previousState == IntersectionState::BothIn && currentState != IntersectionState::BothIn)
            {
                IntersectionData temp = intersection;
                temp.SetCollisionSurface(this);
                //temp.SetDetailedSurface(intersection.GetCollisionSurface());

                intersectionData->push_back(temp);
            }
            break;

        case CsgOperation::Difference:
            if (previousState != IntersectionState::LeftIn && currentState == IntersectionState::LeftIn) // Entrance
            {
                IntersectionData temp = intersection;
                if (temp.GetCollisionSurface() == _rightSurface)
                    temp.SetNormal(-temp.GetNormal());

                temp.SetCollisionSurface(this);
                //temp.SetDetailedSurface(intersection.GetCollisionSurface());

                intersectionData->push_back(temp);
            }
            else if (previousState == IntersectionState::LeftIn && currentState != IntersectionState::LeftIn) // Exit
            {
                IntersectionData temp = intersection;
                if (temp.GetCollisionSurface() == _rightSurface)
                    temp.SetNormal(-temp.GetNormal());

                temp.SetCollisionSurface(this);
                //temp.SetDetailedSurface(intersection.GetCollisionSurface());

                intersectionData->push_back(temp);
            }
            break;
        }
    }

    return this;
}

const Surface* CsgSurface::GetLeftSurface() const
{
    return _leftSurface;
}

const Surface* CsgSurface::GetRightSurface() const
{
    return _rightSurface;
}

CsgOperation CsgSurface::GetOperation() const
{
    return _operation;
}