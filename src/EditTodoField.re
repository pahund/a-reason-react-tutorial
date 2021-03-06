open Utils;

type state = {
  text: string,
  inputElement: ref(option(Dom.element))
};

let component = ReasonReact.reducerComponent("EditTodoField");

let setInputElement = (theRef, {ReasonReact.state}) => state.inputElement := Js.toOption(theRef);

let placeCursorInTextField = (theRef) => {
  Js.log("focus");
  let o = ReactDOMRe.domElementToObj(theRef);
  ignore(o##focus());
  o##setSelectionRange(1000, 1001)
};

let make = (~initialText, ~onSubmit, _) => {
  ...component,
  initialState: () => {text: initialText, inputElement: ref(None)},
  reducer: (newText, state) => ReasonReact.Update({...state, text: newText}),
  didMount: ({state}) => {
    Js.log("did mount");
    switch state.inputElement^ {
    | None => ()
    | Some(r) => placeCursorInTextField(r)
    };
    ReasonReact.Update(state)
  },
  render: ({state: {text}, reduce, handle}) =>
    <input
      value=text
      _type="text"
      ref=(handle(setInputElement))
      placeholder="Todo description"
      onChange=(reduce((evt) => valueFromEvent(evt)))
      onKeyDown=(
        (evt) =>
          if (ReactEventRe.Keyboard.key(evt) == "Enter") {
            onSubmit(text);
            (reduce(() => ""))()
          } else if (ReactEventRe.Keyboard.key(evt) == "Escape") {
            onSubmit(initialText);
            (reduce(() => ""))()
          }
      )
    />
};