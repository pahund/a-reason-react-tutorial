open Utils;

type state = {
  text: string,
  inputElement: ref(option(Dom.element))
};

let component = ReasonReact.reducerComponent("EditTodoField");

let setInputElement = (theRef, {ReasonReact.state}) =>
  state.inputElement := Js.Nullable.to_opt(theRef);

let make = (~initialText, ~onSubmit, _) => {
  ...component,
  initialState: () => {text: initialText, inputElement: ref(None)},
  reducer: (newText, state) => ReasonReact.Update({...state, text: newText}),
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