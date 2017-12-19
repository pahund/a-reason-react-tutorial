open Utils;

open Types;

let component = ReasonReact.statelessComponent("TodoItem");

let getClassName = ({completed}) => "item" ++ (completed ? " completed" : "");

let make = (~item, ~onToggle, _) => {
  ...component,
  render: (_) =>
    <div className=(getClassName(item))>
      <input
        _type="checkbox"
        onChange=((_) => onToggle())
        checked=(Js.Boolean.to_js_boolean(item.completed))
      />
      (str(item.title))
    </div>
};