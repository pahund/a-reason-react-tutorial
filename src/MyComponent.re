type state = string;

let component = ReasonReact.reducerComponent("MyComponent");

let make = (_) => {
  ...component,
  initialState: () => "hotpink",
  reducer: (newColor, _color) => ReasonReact.Update(newColor),
  render: ({state: color, reduce}) =>
    <div onClick=(reduce((_) => "lime")) style=(ReactDOMRe.Style.make(~backgroundColor=color, ()))>
      (ReasonReact.stringToElement("Click Me"))
    </div>
};