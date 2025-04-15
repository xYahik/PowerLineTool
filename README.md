# Unreal Engine – Power Line Tool Project

Projekt Unreal Engine stworzony na wersji 5.4.4 zawierający narzędzie do generowania słupów energetycznych oraz łączenia ich linkami. Narzędzie zostało stworzone z użyciem **Editor Utility Widget** i umożliwia szybkie oraz intuicyjne rozmieszczanie i modyfikację słupów wraz z przewodami na mapie.

## Zawartość projektu

- **Assety**:
  - Domyślne assety Unreal Engine
  - Słupy energetyczne pochodzące z assetu **IndustrialArea**

- **Mapa**:
  - Domyślna mapa o nazwie `NewMap1`, na której użyto narzędzia do wygenerowania pseudo infrastruktury energetycznej

- **Narzędzie**:
  - Nazwa: `WBP_PowerLineTool`
  - Lokalizacja: `Content/EditorUtils/`

## Funkcje narzędzia

- **Wybór mesha słupa** – możliwość wyboru modelu słupa używanego do generacji
- **Tworzenie pojedynczego słupa** – umieszczanie słupa dokładnie w miejscu, w które patrzy kamera edytora
- **Usuwanie słupów** – szybkie usuwanie zaznaczonych elementów
- **Zmiana meshy słupów** – szybka zmiana meshy zaznaczonych elementów
- **Łączenie słupów przewodami** – tworzenie linków (przewodów) między zaznaczonymi słupami
- **Rozłączanie przewodów** – usuwanie istniejących połączeń między słupami
- **Snap do podłoża** – dopasowanie pozycji zaznaczonych słupów do wysokości terenu na podstawie Trace Channel'u (Ground)
- **Obrót słupów** – obracanie zaznaczonych słupów w krokach co 15° (w lewo lub w prawo)
- **Tworzenie spline'a** – wygenerowanie obiektu zawierajacego spline'a na podstawie którego możemy wygenerować słupy energetyczne
- **Generowanie słupów na spline'ie** – automatyczne rozstawianie słupów wzdłuż utworzonego spline'a



---
