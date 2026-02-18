# COPILOT.md - AI Agent Workflow Guide

**MiniVibes Challenge**: Building ambitious projects in limited time with constrained resources.

---

## Table of Contents
1. [Challenge Overview](#challenge-overview)
2. [Project Workflow](#project-workflow)
3. [Specification Requirements](#specification-requirements)
4. [Development Constraints](#development-constraints)
5. [Resource Budget](#resource-budget)
6. [Git Workflow](#git-workflow)
7. [Prompting Guidelines](#prompting-guidelines)
8. [Session Documentation](#session-documentation)

---

## Challenge Overview

### The MiniVibes Challenge
Each project follows strict constraints designed to teach **vibe coding** - the skill of effectively collaborating with AI agents.

### Key Metrics
- **Time**: 1 day per project
- **Token Budget**: Limited (use mini models with 0.33x multiplier mostly)
- **Premium Requests**: 1 per project/day maximum
- **Goal**: Production-quality, feature-complete applications

### Core Philosophy
> **"Premium Is Scarce. Skill Is Not."**

Excellence comes from smart prompting, strategic use of resources, and understanding when to use premium vs. mini models.

---

## Project Workflow

### Phase 1: Specification (Use mini model)
**Goal**: Complete, validated specification before any coding.

The agent must produce a **comprehensive specification** that includes:

1. **Project Objective**
   - Clear description of what's being built
   - User-facing features and behaviors
   - Success criteria

2. **Functional Breakdown**
   - Front-end components and their responsibilities
   - Back-end services (if applicable)
   - APIs and data flow
   - External integrations

3. **Technical Stack**
   - Languages, frameworks, libraries
   - Build tools, development tools, testing frameworks
   - Database schema (if applicable)
   - Package manager and version constraints

4. **File Structure & Organization**
   - Complete directory layout
   - Naming conventions
   - Module boundaries

5. **Development Strategy**
   - Order of implementation (what to build first)
   - Dependency graph (what must exist before what)
   - Validation checkpoints
   - Integration points

6. **Rendering & Fidelity Rules**
   - Visual/behavioral targets (link to reference if applicable)
   - Acceptance criteria for each module
   - Performance targets (if relevant)
   - Browser/environment requirements

7. **Resource Constraints**
   - How premium requests will be used
   - Mini model tasks
   - Token-saving strategies

**Validation Gate**: Human must review and approve specification before Phase 2 begins.

---

### Phase 2: Development (Use mini models primarily)
**Goal**: Build features iteratively within token budget.

**Guidelines for Agent**:

1. **Implement in Priority Order**
   - Follow the specification's development strategy
   - Build vertical slices (feature-complete, end-to-end functionality)
   - Don't start new features until current ones are stable

2. **Test Continuously**
   - Run tests before each commit
   - Verify features match fidelity rules
   - Get human approval for major features

3. **Keep Context Clean**
   - Reference the specification frequently
   - Don't diverge from spec without approval
   - Summarize progress in commit messages

4. **Commit Frequently with Quality Messages**
   - One logical feature per commit
   - Clear, descriptive commit messages
   - Include reference to specification if relevant
   - Use conventional commits: `feat:`, `fix:`, `refactor:`, `docs:`, `test:`

5. **Use Premium Requests Strategically**
   - Only 1 premium request per day
   - Reserve for: architecture decisions, complex algorithms, debugging stuck issues
   - Document exactly what the premium request was used for in SESSION.md

---

### Phase 3: Refinement & Polish (Use mini models)
**Goal**: Address edge cases, improve UX, document code.

**If time permits**:
- Add error handling
- Improve error messages
- Polish UI/UX
- Add comments to complex code
- Update documentation

---

### Throughout development 
**Goal**: Document everything for submission.

Create `SESSION.md` - a record of all prompts. 
Run `/session` command and include output. 

**[Timestamp] - Specification Request**
```
[Prompt will be logged here]
[Model: Mini]
[Status: Completed/In Progress]
```

**[Timestamp] - [Feature Name]**
```
[Prompt will be logged here]
[Model: Mini/Premium]
[Status: Completed/In Progress]
---

## Specification Requirements

Every project MUST include a complete specification before development begins which the developers will oversee and finalise.

### Template for Specification

```markdown
# [Project Name] - Specification

## 1. Project Overview
[Brief description of what's being built]

## 2. Functional Breakdown
### Frontend
- Component A: Responsibilities, inputs, outputs
- Component B: Responsibilities, inputs, outputs
...

### Backend (if applicable)
- Service A: Purpose, endpoints, data contracts
- Service B: Purpose, endpoints, data contracts
...

## 3. Technical Stack
- Language: [Version]
- Framework: [Version]
- Build Tool: [Tool]
- Testing: [Framework]
- Database: [Type and schema if applicable]
- Other dependencies: [List with versions]

## 4. File Structure
\`\`\`
src/
├── components/
│   ├── ComponentA.js
│   └── ComponentB.js
├── services/
│   └── api.js
├── utils/
│   └── helpers.js
└── index.js
\`\`\`

## 5. Development Strategy
### Phase 1: Foundation
1. Set up project structure
2. Install and configure tools
3. Create base components

### Phase 2: Core Features
1. Feature A
2. Feature B
3. Feature C

### Phase 3: Polish
1. Error handling
2. UI refinements
3. Documentation

## 6. Rendering & Fidelity Rules
- [Reference to original project if copying]
- Visual target: [Description or link]
- Behavioral requirements: [List]
- Performance target: [Metrics if applicable]

## 7. Resource Plan
- Premium requests: 1 (for [specific purpose])
- Mini model usage: [Phases 1, 2, 3]
- Estimated token usage: [If known]
```

---

## Development Constraints

### Hard Requirements
✅ **Must Have**:
- `COPILOT.md` documenting all prompts and interactions
- Git history with intelligent, descriptive commits
- All code generated by AI agent (no copy-paste from external sources)
- Dockerized application (working Docker setup)
- `SESSION.md` at end of day

### Soft Requirements (Bonus)
🎁 **Nice to Have**:
- Unit tests
- Security best practices (no SQL injection, XSS, input validation)
- Consistent code formatting with automated tools
- Database usage (relational or NoSQL) when appropriate
- Multiple agents with Git worktrees

### Code Quality Standards
- No hardcoded values (use constants/config)
- Functions do one thing well
- Comments only for "why", not "what"
- Error handling for edge cases
- Consistent naming conventions

---

## Resource Budget

### Daily Resource Allocation

| Phase | Model | Purpose |
|-------|-------|---------|
| Specification | Mini | Write complete spec, get feedback, iterate |
| Development | Mini | 90% of coding tasks |
| Development | Premium | 1 request - use strategically |
| Polish | Mini | Error handling, docs, UX improvements |
| Wrap-up | Mini | Final docs, SESSION.md |

### Token-Saving Strategies

1. **Be Specific in Prompts**
   - Include exact file paths
   - Reference spec sections, don't repeat them
   - Use code snippets instead of descriptions

2. **Batch Related Tasks**
   - Group similar fixes into one prompt
   - Create multiple files in single request
   - Ask for multiple functions at once

3. **Reuse Context**
   - Keep specification available
   - Reference previous solutions
   - Don't ask same questions twice

4. **Incremental Development**
   - Build and test small pieces
   - Don't ask for entire features at once
   - Integrate gradually

---

## Git Workflow

### Commit Message Format

```
<type>(<scope>): <subject>

<body>

<footer>

Co-authored-by: Copilot <223556219+Copilot@users.noreply.github.com>
```

### Types
- `feat`: New feature
- `fix`: Bug fix
- `refactor`: Code restructuring without behavioral change
- `docs`: Documentation changes
- `style`: Formatting, linting changes
- `test`: Test additions or updates
- `chore`: Build, dependency, config changes

### Examples
```
feat(game-engine): implement track rendering with Three.js
fix(physics): correct collision detection on curves
refactor(ui): extract button component for reusability
docs(setup): add Docker usage instructions
test(physics): add collision test suite
```

### Commit Discipline
- Commit after each working feature
- Don't commit broken code
- One logical change per commit
- Write clear, actionable messages

