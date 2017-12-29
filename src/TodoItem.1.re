type item = {
  id: int,
  title: string,
  completed: bool
};

type style = {
  root: ReactDOMRe.style,
  completed: ReactDOMRe.style
};

let str = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("TodoItem");

let styles = {
  root: ReactDOMRe.Style.make(), /* add root styles here */
  completed: ReactDOMRe.Style.make(~opacity="0.666", ~textDecoration="line-through", ())
};

let make = (~item: item, ~onToggle, _) => {
  ...component,
  render: (_) => {
    let style = styles.root;
    let style = item.completed ? ReactDOMRe.Style.combine(style, styles.completed) : style;
    <div style>
      <input
        _type="checkbox"
        onChange=((_) => onToggle())
        checked=(Js.Boolean.to_js_boolean(item.completed))
      />
      <label> (str(item.title)) </label>
    </div>
  }
};