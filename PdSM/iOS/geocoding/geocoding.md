## Location-Based Apps
In iOS divise nelle 2 categorie:
1. **Core Location**:
  - Objective-C API
  - Informazioni sull'orientamento e la posizione dell'utente
  - Importare con: `#import <CoreLocation/CoreLocation.h>`
  - Linkare il Core Location Framework: Selezionare il progetto > Build Phases > Link Binary With Libraries > Aggiungere `CoreLocation.framework`
  - Se i location services sono necessari, `Info.plist` deve contenere un entry per la chiave `Required Device Capabilities` con valore `location-services`
  - iOS si preoccupa di usare diversi sistemi HW (Wi-Fi, GPS, cellular data) per ottenere informazioni di location
    - noi abbiamo un'interfaccia standard: **standard location service** (configurabile, general-purpose, più comune)
	- **significant-change location service**: low-power location service che può svegliare un app quande è sospesa o ferma (iOS4+)
  - Più precisione si richiede, più sono *resource intensive* 
2. **Map Kit**:
  - Supporto per mostrare, annotare e gestire mappe
  - Visualizzazione street-level e mappe satellitari
  - Zoom, pan delle mappe
  - Le mappe possono essere annotate con informazioni custom
  - Importare con: `#import <MapKit/MapKit.h>`
  - Linkare il MapKit Framework: Selezionare il progetto > Build Phases > Link Binary With Libraries > Aggiungere `MapKit.framework`


### Configurazione e Core Location
- Servizio Gestido da: `CLLocationManager`
  1. Location Data
  2. App Event Notifications
- Proprietà da Configurare
  1. `CLLocationAccuracy desiredAccuracy`
     - `kCLLocationAccuracyBestForNavigation`: Precisione massima + altri sensori (app di navigazione)
     - `kCLLocationAccuracyBest`: Precisione massima
     - `kCLLocationAccuracyNearestTenMeters`: Entro 10 metri dal target
     - `kCLLocationAccuracyNearestHundredMeters`: Entro 100 metri dal target
     - `kCLLocationAccuracyNearestKilometer`: Entro 1 kilometro dal target
     - `kCLLocationAccuracyNearestThreeKilometers`: Entro 3 kilometri dal target
  2. `CLLocationDistance distanceFilter`
     - Minima distanza in metri che deve essere percorsa prima di generare un nuovo evento di update
  3. `CLActivityType activityType`: Tipo di utilizzo del servizio da parte dell'utente
     - `CLActivityTypeOther`: Default, per qualsiasi altra cosa
     - `CLActivityAutomotiveNavigation`
     - `CLActivityOtherNavigation`
     - `CLActivityFitness`
- il manager può essere fatto partire e fermare con i metodi
	```objective-c
	[locationManager startUpdatingLocation];
	[locationManager startUpdatingHeading];
	[locationManager stopUpdatingLocation];
	[locationManager stopUpdatingHeading];
	```
- il manager può anche monitorare eventi relativi a specifiche regioni spaziali
  - Entrare e uscire da queste "geofence" può generare speciali eventi
  - `[locationManager startMonitoringForRegion:region];`
  - `[locationManager stopMonitoringForRegion:region];`


### Notifiche tramite CLLocationManagerDelegate
- Si può definire un oggetto come conformante al protocollo `CLLocationManagerDelegate` che quindi riceve notifiche di eventi di location
- `CLLocation` è il tipo di dato strutturato generato da `CLLocationManager` e contiene:
  1. coordinate geografiche e altitudine
- Metodi del protocollo:
```objective-c
//La più recente è l'ultima location dell'array
- (void) locationManager:(CLLocationManager*)manager didUpdateLocations:(NSArray*)locations
- (void) locationManager:(CLLocationManager*)manager didUpdateHeading:(CLHeading*)newHeading

- (void) locationManagerDidPauseLocationUpdates:(CLLocationManager*)manager
- (void) locationManagerDidResumeLocationUpdates:(CLLocationManager*)manager
// ed altri ...
```

***Esempio di Location Monitoring nel file `location.m`***

### Simulating Locations in the simulator
- File GPX aggiunti al progetto
- GPX sono file XML che hanno un formato specifico per definire posizioni geografiche
- Esempio: `position.gpx`
- Una volta che il GPX è aggiunto al progetto:
- Simulator > Debug > Simulate Location > "Nome della location definita nel GPX"

## Geocoding
- Classe: `CLGeocoder`
- Offre servizi per convertire tra coordinate specifiche di latitudine e longitudine e la rappresentazione user-friendly di quelle coordinate
- *Forward-geocoding*: Richieste che prendono un indirizzo user-readable e trovano le coordinate geografiche corrispondenti
- *Reverse-geocoding*: Richieste che prendono le coordinate geografiche corrispondenti e restituiscono un indirizzo user-friendly
  - `reverseGeocodeLocation:CLLocation* completionHandler:CLGeocodeCompletionHandler`
  - il completionHandler è definito come: `typedef void (^CLGeocodeCompletionHandler)(NSArray* placemark, NSError* error)`
    - Manda i location data al geocoding server e restituisce in modo asincrono i risultati
    - **Viene eseguito sul main thread**
    - Per la maggior parte delle richieste di geocoding il placemark array dovrebbe contenere 1 solo oggetto
- I Risultati sono ritornati tramite un oggetto di tipo `CLPlacemark`
- Esempio in `location.m`

### Aggiungere e Gestire una mappa
- `MKMapView`: subclass di `UIView`
- Intefaccia per presentare map data
- Può essere aggiunta:
  - Programmaticamente con `alloc/initWithFrame:`
  - Nello storyboard dalla palette
- Configurare Area visibile
	```objective-c
	MKCoordinateRegion mapRegion;
	mapRegion.center = location.coordinate;
	mapRegion.span.latitudeDelta = 0.1;
	mapRegion.span.longitudeDelta = 0.1;
	//Centra la mappa nella regione specificata
	[self.mapView setRegion:mapRegion animated:YES]
	```
- Per spostarsi senza zoommare si può settare la proprietà centerCoordinate in questo modo
	```objective-c
	CLLocationCoordinate2D newCenter = CLLocationCoordinate2DMake(loc.latitude, loc.longitude);
	self.mapView.centerCoordinate = newCenter;
	```
- Per mostrare la posizione dell'utente si cambia la proprietà: `self.mapView.showsUserLocation = YES`
- Le annotazioni sulla mappa sono rappresentate da oggetti: `MKAnnotationView` e sono composte da: coordinate, titolo, e sottotitolo
  - 2 Viste aggiuntive possono essere aggiunte al callout collegato all'annotazione: `leftCalloutAccessoryView` e `leftCalloutAccessoryView`
  - Si aggiunge alla mappa un oggetto conforme al protocollo: `MKAnnotation` che definisce 3 properties
  	1. **required property `coordinate`** di tipo `CLLocationCoordinate2D`
  	2. *optional `title`* di tipo `NSString*`
  	3. *optional `subtitle`* dello stesso tiop del titolo
  - Metodi:
	```objective-c
	//id<MKAnnotation> perché può essere qualsiasi oggetto basta che sia conforme al protocollo MKAnnotation
	- (void) addAnnotation:(id<MKAnnotation>)annotation
	- (void) addAnnotations:(NSArray*)annotations
	- (void) removeAnnotation:(id<MKAnnotation>)annotation
	- (void) removeAnnotations:(NSArray*)annotations
	```
  - Si può subclassare la `MKAnnotationView` per modificare le cose grafiche del marker: il callout funziona se la proprietà `canShowCallout` = YES
- **`MKMapViewDelegate`**
  - Protocollo delegate per comportamenti extra:
    - Map position changes
    - Loading map data events
    - User Location Changes
    - Manage Annotation views
      - `- (MKAnnotationView*)mapView:(MKMapView*)mapView viewForAnnotation:(id<MKAnnotation>)annotation`
      - Chiamato quando un annotazione deve essere posizionata sulla mappa
      - Esempio:
	  ![map_annotations](annotation_views.png)
    - Annotation View drag events
    - Selection of annotation views
      - Delegate notificato quando un annotazione è selezionata
      - Lazy initialization del contenuto del callout
		```objective-c
		- (void) mapView:(MKMapView*)mapView didSelectAnnotationView:(MKAnnotationView*)view{
			if ([view.leftCalloutAccessoryView isKindOfClass:[UIImageView class]]) {
				UIImageView* image = (UIImageView*)view.leftCalloutAccessoryView;
				//image.image = ...; Load from network using grand central dispatch
			}
		}
		```
      - `(void) mapView:(MKMapView*)mapView annotationView:(MKAnnotationView*)view calloutAccessoryControlTapped:(UIControl*)control`
        - Se si vuole fare una segue bisogna farla programmaticamente
		1. Nello storyboard si crea una segue manuale tra i 2 controller
		2. Assegnare un identificatore alla segue per referenziarla nel codice
		3. Eseguire il metodo `performSegueWithIdentifier:sender:` del ViewController configurando identificatore e sender (annotation)