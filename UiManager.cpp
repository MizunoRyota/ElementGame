#include "stdafx.hpp"
#include "UiManager.hpp"

UiManager::UiManager() = default;
UiManager::~UiManager() = default;

void UiManager::AddElement(const std::shared_ptr<IUiElement>& element)
{
    if (!element) return;
    elements_.push_back(element);
    needSort_ = true;
}

void UiManager::RemoveElement(const std::shared_ptr<IUiElement>& element)
{
    elements_.erase(std::remove(elements_.begin(), elements_.end(), element), elements_.end());
}

void UiManager::UpdateTitle()
{
    // Z順再ソート要求チェック
    if (needSort_)
    {
        std::stable_sort(elements_.begin(), elements_.end(), [](const auto& lhs, const auto& rhs) {
            return lhs->GetZ() < rhs->GetZ();
            });
        needSort_ = false;
    }

    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->UpdateTitle();
    }
}

void UiManager::UpdateTutorial()
{
    // Z順再ソート要求チェック
    if (needSort_)
    {
        std::stable_sort(elements_.begin(), elements_.end(), [](const auto& lhs, const auto& rhs) {
            return lhs->GetZ() < rhs->GetZ();
            });
        needSort_ = false;
    }

    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->Update();
    }
}

void UiManager::Update()
{
    // Z順再ソート要求チェック
    if (needSort_)
    {
        std::stable_sort(elements_.begin(), elements_.end(), [](const auto& lhs, const auto& rhs) {
            return lhs->GetZ() < rhs->GetZ();
        });
        needSort_ = false;
    }

    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->Update();
    }
}

void UiManager::UpdateGameClear()
{
    // Z順再ソート要求チェック
    if (needSort_)
    {
        std::stable_sort(elements_.begin(), elements_.end(), [](const auto& lhs, const auto& rhs) {
            return lhs->GetZ() < rhs->GetZ();
            });
        needSort_ = false;
    }

    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->UpdateGameClear();
    }
}

void UiManager::UpdateGameOver()
{
    // Z順再ソート要求チェック
    if (needSort_)
    {
        std::stable_sort(elements_.begin(), elements_.end(), [](const auto& lhs, const auto& rhs) {
            return lhs->GetZ() < rhs->GetZ();
            });
        needSort_ = false;
    }

    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->UpdateGameOver();
    }
}

void UiManager::DrawTitle() const
{
    // Update時にソートされている前提
    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->DrawTitle();
    }
}

void UiManager::DrawTutorial() const
{
    // Update時にソートされている前提
    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->DrawTutorial();
    }
}

void UiManager::Draw() const
{
    // Update時にソートされている前提
    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->Draw();
    }
}

void UiManager::DrawGameClear() const
{
    // Update時にソートされている前提
    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->DrawGameClear();
    }
}

void UiManager::DrawGameOver() const
{
    // Update時にソートされている前提
    for (auto& element : elements_)
    {
        if (!element || !element->IsVisible()) continue;
        element->DrawGameOver();
    }
}
