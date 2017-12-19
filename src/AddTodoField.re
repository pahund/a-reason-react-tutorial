open Utils;

open Types;

type state = string;

let component = ReasonReact.reducerComponent("AddTodoField");

let make = (~onSubmit, _) => {
  ...component,
  initialState: () => "",
  reducer: (newText, _text) => ReasonReact.Update(newText),
  render: ({state: text, reduce}) =>
    <input
      value=text
      _type="text"
      placeholder="Write something to do"
      onChange=(reduce((evt) => valueFromEvent(evt)))
      onKeyDown=(
        (evt) =>
          if (ReactEventRe.Keyboard.key(evt) == "Enter") {
            onSubmit(text);
            (reduce(() => ""))()
          }
      )
    />
};