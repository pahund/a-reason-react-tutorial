open Utils;

type state = {
  text: string,
  inputElement: ref(option(Dom.element))
};

let component = ReasonReact.reducerComponent("EditTodoField");

let setInputElement = (theRef, {ReasonReact.state}) => state.inputElement := Js.toOption(theRef);

let placeCursorInTextField = (theRef) => {
  let o = ReactDOMRe.domElementToObj(theRef);
  ignore(o##focus());
  o##setSelectionRange(1000, 1001)
};

let make = (~initialText, ~onSubmit, _) => {
  ...component,
  initialState: () => {text: initialText, inputElement: ref(None)},
  reducer: (newText, state) => ReasonReact.Update({...state, text: newText}),
  didMount: ({state}) => {
    switch state.inputElement^ {
    | None => ()
    | Some(r) => placeCursorInTextField(r)
    };
    ReasonReact.Update(state)
  },
  render: ({state: {text}, reduce, handle}) => {
    let save = (_) => onSubmit(text);
    let cancel = (_) => onSubmit(initialText);
    <input
      value=text
      _type="text"
      ref=(handle(setInputElement))
      placeholder="Todo description"
      onChange=(reduce((evt) => valueFromEvent(evt)))
      onBlur=cancel
      onKeyDown=(
        (evt) =>
          if (ReactEventRe.Keyboard.key(evt) == "Enter") {
            save()
          } else if (ReactEventRe.Keyboard.key(evt) == "Escape") {
            cancel()
          }
      )
    />
  }
};