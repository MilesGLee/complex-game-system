# ComplexGameSystem

This Dialogue System consists of two components, the Dialogue Listener and the Dialogue Speaker.

Dialogue Listener:

The Dialogue Listener should be attached to your player character. You do not have to change any of the visible variables in the details menu,
instead you will be operating the listener from a blueprint. It is advised to use the level blueprint. To begin, create the UI Widget you want
to use for your dialogue, this widget should consist of at least one text block component, but is advised to consist of two text block components
(one text for the dialogue, the other for the title), and three button components. Then create a reference to your players Dialogue Listener in
blueprint and connect the function 'LinkUIAll' (Or LinkUIMain for only text, or LinkUIMainName for text dialogue and title) to 'EventBeginPlay'.

Dialogue Speaker:

The Dialogue Speaker will be the component attached to all entities you wish the player to converse with. The Speaker component consists of multiple
variables you are expected to edit for it to work.

-Name: This is a string input box, you can enter any string you want to have that string appear in the UI if you have the Title text block linked.

-Can Skip: If this bool is true, the player will be able to skip the dialogue that is currently being written by interacting with the speaker again.

-Loop: This enumerator has two options for what you want the speaker to do when it reaches the end of its dialogue.

-Pieces of Dialogue: This is a list of Dialogue Pieces. Each piece has its own variables you edit to change how the listener reads it.
Generally the listener will be given a reference to the Dialogue Speaker and will read each dialogue piece one at a time. The player will
interact with the speaker to continue to the next piece.

>Piece Index: The number of the piece in the list. This is generally the order in which the listener will read them.

>Speech Index: This index is editable and is the order the listener will read the piece of dialogue. If the number is the same as the previous piece
the Listener will treat both pieces as the same, and write them one after the other without requiring an interaction from the player.

>Text: The string that will be written out to the UI.

>Duration: The time it takes to write out the Text.

>Delay: The time the listener will wait before writing out the Text.

>Has Completion Event: If toggled true, the event can be linked in blueprint using the Piece Index in a switch int statement.

>Is Question: If toggled true, the following three text answer boxes will be used and the listener will wait until a response is given to continue.

>Answer 1-3: String inputs to be used if a question is asked, if left blank, the corresponding button will stay invisible.

>Is Locked by Progression: If true, this piece will not ignored unless the speaker is at that current progression.

>Progression ID: The Speaker has an invisible to the editor int variable that can be changed in blueprint called Progression, if the Progression
int is the same as the Progression ID and Is Locked is true, then this piece can be written.
