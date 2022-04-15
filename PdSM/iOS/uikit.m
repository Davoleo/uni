//UIColor represents a color
//- RGB
//- HSB
//It also handles transparency.
//System color constants are provided as Methods: blackColor, redColor, greenColor...


//Fonts (UIFont)
//Font Predefinito per certi stili di testo
UIFont* font = [UIFont preferredFontForTextStyle:UIFontTextStyleHeadline];
//Font with name
+(UIFont*)fontWithName:(NSString*)fontName size:(CGFloat)fontSize
UIFont* font = [UIFont fontWithName:@"HelveticaNeue-Bold" size:15.0];
//FontForFamilyName
+(NSArray) fontNamesForFamilyName:(NSString*)familyName

//NSAttributedString serve per specificare degli attributi di una certa stringa:
//  Stroke width, color ...
//  Key/Value Pairs
//Non è una sottoclasse di NSString!
-(id)initWithString:(NSString*)aString
-(id)initWithAttributedString:(NSAttributedString*)attributedString
-(id)initWithString:(NSString*)string attributes:(NSDictionary*)attributes
//esiste anche NSMutableAttributedString per cambiare dinamicamente caratteri e gli attributi

//Example
NSString* string = @"testo piccolo, testo grande!";
NSMutableAttributedString* stringAttrs = [[NSMutableAttributedString alloc] initWithString:string];
[stringAttrs addAttribute:NSFontAttributeName value:[UIFont systemFontOfSize:24.0] range:NSMakeRange(15, 13)];
[stringAttrs addAttribute:NSFontAttributeName value:[UIColor redColor] range:NSMakeRange(6, 7)];

//UIView: generic superClass
//CGRect è un insieme di origin e size
//Properties:
//- frame (CGRect): origine e dimensioni della view nel sistema di coordinate della sua superclasse
//- bounds (CGRect): le dimensioni interne della view per come si vedono
//- center (CGPoint): le coordinate del punto centrale dell'area rettangolare
//- backgroundColor (UIColor*): background color (default nil = transparent)
//- alpha (CGFloat): 0.0 = transparent | 1.0 = opaque
//- hidden (BOOL): YES = view invisibile | NO = view visible
//- userInteractionEnabled (BOOL): NO = user events ignored

//UILabel: static text on fixed number of lines
//
//Properties:
//- text (NSString*): displayed Text
//- font (UIFont*): text font
//- textColor (UIColor*): text color
//- textAlignment (NSTextAlignment): alignment through NSTextAlignmentLeft,...
//- attributedText (NSAttributedString*): styled text displayed
//- numberOfLines (NSInteger): 

//UIKit Controls: Buttons, Date Pickers, Page Controls, Segmented Controls, Text Fields, Sliders, Steppers, Switches
//They react to user events
//Control State: Stato del controllo in un determinato istante
//- Specific Behaviour e appearance può essere specificato per ogni stato del controllo
//Control Events: sono tanti

//Target-action
//Binding target action ad un control event
//1. Programmaticamente
[self.mySlider addTarget:self action:@selector(myAction:) forControlEvents:UIControlEventValueChanged];
//2. With connection inspector in Interface Builder (drag event to the handler)
//3. Ctrl click the slider e draggare l'evento al target object nello storyboard

//UIButton
//Interazione con utente tramite tap
//Textual or image content
//Quando è tapped cambia stato in highlighted
//Impostare proprietà in modo programmatico
- (void)setTitle:(NSString*)title forState(UIControlState)state
- (void)setAttributedTitle:(NSAttributedString*)title forState(UIControlState)state
- (void)setImage:(UIImage*)image forState(UIControlState)state
- (void)setBackroundImage:(UIImage*)image forState(UIControlState)state

//UISlider
//- Permettono modificazione interattiva di valore continuo nell'app
//Default Values: minimumValue = 0, maximumValue = 1 e value = 0.5
//Proprietà dei colori: maximumTrackTintColor, thumbTintColor, minimumTrackTintColor

//UISwitch
//- Permette di accedere o spegnere qualcosa
//- underlying bool property: on
//- Style props: onTintColor, thumbTintColor, tintColor

//UITextField
//properties: text, attributedText
//- placeholder, attributedPlaceholder [Testo quando non c'è scritto niente dentro]
//- clearButtonMode (mette o toglie il tasto per pulire il field)
//- può essere stilizzato ccon: font, textAlignment, textColor
//- Può anche essere settato lo stile e layout della tastiera con (UITextInputTraits)

//Keyboard Management
//Tastiera importante per dispositivi touch
//Copre una certa area della view
//La tastiera diventa il **first responder**
//Necessario gestirla correttamente: 
//- Potrebbe essere necessario far scorrere la view in modo che non venga coperta dalla tastiera
//- Necessario far sparire la tastiera manualmente in certi casi
//Necessario trasformare la background view in un UIControl in modo che possa ricevere tap events
//Definire un IBAction nel view controller che venga invocato quando l'utente tocca all'interno del controllo
//Quando la view di background è toccata la tastiera può essere dismessa con:
[textField resignFirstResponder]

//UITextView
//Più potente del field: multiline, editable, selectable, scrollable
// 2 Proprietà
//- textNSString per testo normale; proprietà che affectano il text style sono font, textColor, textAlignment
//- attributedText:NSAttributedString per testo stilizzato
//- textStorage (NSTextStorage): efficient text manipulation (e aggiornamento automatico del controllo dopo la modifica)
//- editable (BOOL): se il receiver è modificabile
//- selectable (BOOL): se il testo è selezionabile
//- selectedRange (NSRange): range di selezione corrente nella text view

//UITextViewDelegate
//Protocollo associato ai controlli più avanzati per modificarli in concomitanza con eventi speciali
//Esempio
-(BOOL)textViewShouldBeginEditing:(UITextField*)textView
-(BOOL)textViewShouldEndEditing:(UITextField*)textView
-(void)textViewDidBeginEditing:(UITextField*)textView
-(void)textViewDidChange:(UITextField*)textView
-(void)textViewDidChangeSelection:(UITextField*)textView
-(void)textViewDidEndEditing:(UITextField*)textView

//Notifications
//Un modo di interagire tra oggetti oltre a message passing
//Si basa su NSNotificationCenter classe che offre il meccanismo di broadcasting all'interno del programma (broker)
//Modo per ottenere una reference a al notification center (è un singleton)
NSNotificationCenter* notifCenter = [NSNotificationCenter defaultCenter];
//è importante unregistrare dalle notifiche quando non è necessario per evitare crash
// Di solito ci si registra quando la view appare e unregistra quando sparisce (quando le notifiche devono essere ricevute quando la view è offscreen ci si unregistra in dealloc [raro])
//Registering for notifications:
- (void)addObserver:(id)notificationObserver	//Ricevitore della notifica che ha il metodo da eseguire
		selector:(SEL)notificationSelector	 	//Metodo da eseguire
		name:(NSString*)notificationName		//Nome della notifica
		object:(id)notificationSender			//sorgente di notifiche (nil = any object)
//Example:
[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(aMethod) name:UIKeyboardWillShowNotification object:nil]

//Unregistering from notifications
-(void)removeObserver:(id) notificationObserver
		name:(NSString*)notificationName
		object:(id)notificationSender
//Example
[[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil]

//Generating Notifications
-(void)postNotificationName:(NSString*) notificationName
		object:(id)notificationSender
		userInfo:(NSDictionary*)userInfo	//<- Arricchisce la notifica di informazioni contestuali
//Example:
[[NSNotificationCenter defaultCenter] postNotificationName:@"MyNotification" object:self userInfo:nil]

//System Notification for keyboard-related events: UIKeyboard<Will|Did><Show|Hide>Notification

//UIScrollView permettono di vedere content che è più largo delle view boundaries
//sono aggiunte vertical e horizontal scroll per indicare che c'è content in più da vedere
//UIScrollView è una view la cui origin è aggiustabile sopra alla content view
//Clippa il contenuto al frame
//Permette anche lo zoom
//Contenuto: qualsiasi UIView
//Aggiungere una view ad una scrollview
UIImageView* imageView = [[UIImageView alloc] initWithIamge:image];
[scrollView addSubview:imageView];
//scrollView.contentSize = CGSizeMake(3000, 3000);
scrollView.contentSize = imageView.bounds.size;
//^ Importante da fare perché altrimenti non funziona

//contentOffset posizione della scrollview rispetto al content
scrollView.contentOffset.x, scrollView.contentOffset.y
//bounds del rettangolo visibile
scrollView.bounds.origin.x, scrollView.bounds.origin.y
//Raccomandato aggiungere le scroll view dallo storyboard e poi le subview programmaticamente
//Scrollare programmaticamente
- (void) scrollRectToVisible:(CGRect)rect animated:(BOOL)animated
//directionalLockEnabled controlla se è locckato in un certo asse lo scroll da quando inizia
//Abilitare lo zoom
self.scrollView.minimumZoomScale = 0.5; //50%
self.scrollView.maximumZoomScale = 3.0; //300%
//Assegnarsi come delegate
self.scrollView.delegate = self;
//sulla definizione della classe si deve aggiungere questo
@interface MyViewController : UIViewController<UIScrollViewDelegate>
//Metodi che si possono implementare
- (UIView*) viewForZoomingInScrollView:(UIScrollView*)sender; //mandatory
- (void) scrollViewDidScroll:(UIScrollView*)scrollView;
- (void) scrollViewDidZoom:(UIScrollView*)scrollView;
- (void) scrollViewWillBeginZooming:(UIScrollView*)scrollView withView:(UIView*)view;
- (void) scrollViewDidEndZooming:(UIScrollView*)scrollView withView:(UIView*)view atScale:(CGFloat)scale;
- (void) scrollViewWillBeginDragging:(UIScrollView*)scrollView;
- (void) scrollViewDidEndDragging:(UIScrollView*)scrollView willDecelerate:(BOOL)decelerate;

//Table View
//Usate per mostrare e modificare liste gerarchiche di informazioni
//è 1-dimensional, solo righe no colonne
//Per n-dimnesioni si combinano diverse table view in un navigation controller
//UITableView è una sottoclasse di UIScrollView
//- Solo Vertical Scrolling
//Può gestire efficientemente grandi quantità di dati
//Esistono stili: plain o grouped
//Possono essere dinamiche (mutable e unpredictable) o statiche (fixed content)
@property UIView* tableHeaderView;
@property UIView* tableFooterView;
//Si possono settare header e footer sia per le table che per le sezioni
//Table Cell Styles
//UITableViewCellStyleDefault
//UITableViewCellStyleSubtitle
//UITableViewCellStyleValue1
//UITableViewCellStyleValue2

//UIController fatto apposta per le TableView
UITableViewController;

//Pull to Refresh
//Spinner in testa alla tabella per fare pull in modo da refresshare i contenuti della tabella
//Classe: UIRefreshControl
//UITableViewController proprietà: refreshing -> enabled attiva questa opzione (il Refresh control appare automaticamente all'interno dell'inspector)
//Ctrl-Draggando dal refresh control al codice si crea un handler
//Esempio
- (IBAction)refreshTableView:(UIRefreshControl*)sender {
	[sender beginRefreshing]; //Starts the spinner
	//... reload data
	[self.tableView reloadData]; //Redraws the cells | Should be linked to the callback of the asynchronous method to retrieve new data
	[sender endRefreshing];
}