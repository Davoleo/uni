# Progetto iOS - MyWeather

### Requirements:
- Sviluppare un’applicazione per la visualizzazione della condizioni meteorologiche
- L’utente visualizza le condizioni meteorologiche attuali e previste per i prossimi N giorni nella sua posizione attuale
- L’utente inserisce una città e visualizza le condizioni meteorologiche attuali e previste per i prossimi N giorni
- L’utente può decidere di salvare la città come “preferita” ed aggiungerla ad una lista di città preferite per un accesso più rapido
- La lista delle città preferite può essere visualizzata su una mappa mettendo come marker un’icona legata alla condizione del meteo


## Sezioni (App Bar in Basso)
- Sezione Preferiti
  - Visualizzazione a Lista 
    - Button nella barra in alto che apre la visualizzazione a mappa
    - Icone negli elementi delle liste related al meteo
    - Temperatura come small tooltip
  - Visualizzazione a Mappa
    - Visualizzazione estesa (la stessa della sezione ricerca) a partire dai Marker della Mappa
    - Icone corrispondenti alla situazione meteorologica
- Sezione Ricerca
  - Text Field In alto per ricerca tramite nome città
  - I singoli item aprono una visualizzazione di dettaglio delle condizioni meteo
- My Position
  - Sezione di dettaglio con informazioni sul meteo nella posizione corrente
  
## Pagina di Dettaglio
- Meteo Corrente
  - Temperatura
  - Le condizioni (Icona e Descrizione)
  - Nome del luogo
  - Velocità e Direzione del Vento
  - Tramonto e Alba
- Previsioni future
  - 

## Impostazioni Possibili
- Dark Mode / Light Mode / Auto
- Degrees Measure System (F°/C°)
- Sezione About
<!--- N Giorni di Stima visualizzata-->

**Some Resources:**
- Weather Icons:
  - https://icons8.com/icon/set/weather/ios-glyphs--black
  - https://icons8.com/icon/set/weather/color
- iOS Weather App Icons: https://support.apple.com/en-gb/guide/iphone/iph4305794fb/ios

- [Alert Dialog](https://stackoverflow.com/questions/4988564/how-to-implement-a-pop-up-dialog-box-in-ios)
- [Alert dialog Buttons](https://stackoverflow.com/questions/24022479/how-would-i-create-a-uialertview-in-swift/33340757#33340757)
- [Custom Accessory view in UITableCell](https://stackoverflow.com/questions/30708818/ios-xcodehow-to-add-accessory-view-to-custom-cell)
- [Container View (Assembled VCs)](https://stackoverflow.com/questions/17499391/ios-nested-view-controllers-view-inside-uiviewcontrollers-view)
- [Container View Controller](https://developer.apple.com/library/archive/featuredarticles/ViewControllerPGforiPhoneOS/ImplementingaContainerViewController.html)
- [Refresh Contents Control](https://developer.apple.com/design/human-interface-guidelines/ios/controls/refresh-content-controls/)
- [Dark Mode Overrides](https://developer.apple.com/documentation/uikit/appearance_customization/supporting_dark_mode_in_your_interface/choosing_a_specific_interface_style_for_your_ios_app?language=objc)
- [Open Link on Safari](https://stackoverflow.com/questions/12416469/how-to-launch-safari-and-open-url-from-ios-app)
- [Checkmark Selected Row (TableView)](https://stackoverflow.com/questions/7982944/checkmark-selected-row-in-uitableviewcell)
- [Scrolling Stack view StackOverflow](https://stackoverflow.com/questions/31668970/is-it-possible-for-uistackview-to-scroll)
  - [Scrolling Stack view Example](https://github.com/ar-juan/uistackview-in-uiscrollview)
### OpenWeatherMap
  - https://openweathermap.org/api
  - https://openweathermap.org/api/one-call-api
  - https://openweathermap.org/current
